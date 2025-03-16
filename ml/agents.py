import numpy as np
import random
import torch
import torch.nn as nn
import torch.optim as optim
from collections import deque

# -----------------------------
# DDPG Agent Components (unchanged)
# -----------------------------
class Actor(nn.Module):
    def __init__(self, state_dim, action_dim, hidden_dim=256):
        super(Actor, self).__init__()
        self.fc1 = nn.Linear(state_dim, hidden_dim)
        self.fc2 = nn.Linear(hidden_dim, hidden_dim)
        self.fc3 = nn.Linear(hidden_dim, action_dim)
    
    def forward(self, state):
        x = torch.relu(self.fc1(state))
        x = torch.relu(self.fc2(x))
        # Bound the outputs between -1 and 1.
        return torch.tanh(self.fc3(x))

class Critic(nn.Module):
    def __init__(self, state_dim, action_dim, hidden_dim=256):
        super(Critic, self).__init__()
        self.fc1 = nn.Linear(state_dim + action_dim, hidden_dim)
        self.fc2 = nn.Linear(hidden_dim, hidden_dim)
        self.fc3 = nn.Linear(hidden_dim, 1)
    
    def forward(self, state, action):
        x = torch.cat([state, action], dim=1)
        x = torch.relu(self.fc1(x))
        x = torch.relu(self.fc2(x))
        return self.fc3(x)

class ReplayBuffer:
    def __init__(self, capacity):
        self.buffer = deque(maxlen=capacity)
    
    def push(self, state, action, reward, next_state, done):
        self.buffer.append((state, action, reward, next_state, done))
    
    def sample(self, batch_size):
        batch = random.sample(self.buffer, batch_size)
        state, action, reward, next_state, done = map(np.stack, zip(*batch))
        return state, action, reward, next_state, done
    
    def __len__(self):
        return len(self.buffer)

class DDPGAgent:
    def __init__(self, state_dim, action_dim, hidden_dim=256,
                 actor_lr=1e-3, critic_lr=1e-3, gamma=0.99, tau=0.005,
                 buffer_capacity=100000, batch_size=64):
        self.state_dim = state_dim
        self.action_dim = action_dim
        self.gamma = gamma
        self.tau = tau
        self.batch_size = batch_size

        self.actor = Actor(state_dim, action_dim, hidden_dim)
        self.actor_target = Actor(state_dim, action_dim, hidden_dim)
        self.actor_target.load_state_dict(self.actor.state_dict())
        self.actor_optimizer = optim.Adam(self.actor.parameters(), lr=actor_lr)

        self.critic = Critic(state_dim, action_dim, hidden_dim)
        self.critic_target = Critic(state_dim, action_dim, hidden_dim)
        self.critic_target.load_state_dict(self.critic.state_dict())
        self.critic_optimizer = optim.Adam(self.critic.parameters(), lr=critic_lr)

        self.replay_buffer = ReplayBuffer(buffer_capacity)
    
    def select_action(self, state, noise_scale=0.1):
        state = torch.FloatTensor(state).unsqueeze(0)
        action = self.actor(state).detach().numpy()[0]
        action += noise_scale * np.random.randn(self.action_dim)
        return np.clip(action, -1, 1)
    
    def update(self):
        if len(self.replay_buffer) < self.batch_size:
            return
        state, action, reward, next_state, done = self.replay_buffer.sample(self.batch_size)
        state = torch.FloatTensor(state)
        action = torch.FloatTensor(action)
        reward = torch.FloatTensor(reward).unsqueeze(1)
        next_state = torch.FloatTensor(next_state)
        done = torch.FloatTensor(np.float32(done)).unsqueeze(1)
        
        with torch.no_grad():
            next_action = self.actor_target(next_state)
            target_q = self.critic_target(next_state, next_action)
            target_value = reward + (1 - done) * self.gamma * target_q
        
        current_q = self.critic(state, action)
        critic_loss = nn.MSELoss()(current_q, target_value)
        self.critic_optimizer.zero_grad()
        critic_loss.backward()
        self.critic_optimizer.step()
        
        actor_loss = -self.critic(state, self.actor(state)).mean()
        self.actor_optimizer.zero_grad()
        actor_loss.backward()
        self.actor_optimizer.step()
        
        for target_param, param in zip(self.actor_target.parameters(), self.actor.parameters()):
            target_param.data.copy_(target_param.data * (1-self.tau) + param.data * self.tau)
        for target_param, param in zip(self.critic_target.parameters(), self.critic.parameters()):
            target_param.data.copy_(target_param.data * (1-self.tau) + param.data * self.tau)

# -----------------------------
# New Competition Environment
# -----------------------------
class CompetitionEnv:
    """
    This environment simulates three competing countries.
    Each country has a state vector: [economy, population, military]
    The overall state is the concatenation of the three countries (9 values total).
    
    The agent (Country 0) chooses a 4-dimensional action:
      - action[0]: War/Diplomacy decision (war if >0, diplomacy if <=0)
      - action[1]: Investment to military
      - action[2]: Investment to economy
      - action[3]: Investment to population
    Resource allocations (a1, a2, a3) are normalized and determine boosts.
    Opponents use a fixed allocation and random war/diplomacy choices.
    """
    def __init__(self):
        self.state_dim = 9
        self.action_dim = 4
        self.reset()
    
    def reset(self):
        # Initialize all countries with equal metrics.
        self.agent = np.array([100.0, 100.0, 100.0])  # [econ, pop, mil]
        self.opp1  = np.array([100.0, 100.0, 100.0])
        self.opp2  = np.array([100.0, 100.0, 100.0])
        return self._get_state()
    
    def _get_state(self):
        return np.concatenate([self.agent, self.opp1, self.opp2])
    
    def step(self, action):
        # Decode agent's decision and resource allocation.
        decision_agent = "war" if action[0] > 0 else "diplomacy"
        alloc_raw = np.array([max(action[1], 0), max(action[2], 0), max(action[3], 0)])
        if alloc_raw.sum() == 0:
            alloc_agent = np.array([1/3, 1/3, 1/3])
        else:
            alloc_agent = alloc_raw / alloc_raw.sum()
        
        # Opponents: fixed allocation and random decision.
        decision_opp1 = "war" if random.random() < 0.5 else "diplomacy"
        decision_opp2 = "war" if random.random() < 0.5 else "diplomacy"
        alloc_opp = np.array([0.3, 0.4, 0.3])  # [military, economy, population]
        
        # Save previous totals for reward computation.
        old_agent_total = self.agent.sum()
        old_opp_avg = (self.opp1.sum() + self.opp2.sum()) / 2.0
        
        # Constants for natural growth and investment gains.
        natural_econ = 2.0
        natural_pop = 1.0
        military_decay = 0.1
        gain_mil = 5.0
        gain_econ = 4.0
        gain_pop = 3.0
        diplomacy_bonus_econ = 5.0
        diplomacy_bonus_pop = 2.0
        
        # Update function for each country.
        def update_country(metrics, alloc):
            new_metrics = np.empty_like(metrics)
            new_metrics[0] = metrics[0] + natural_econ + gain_econ * alloc[1]  # economy
            new_metrics[1] = metrics[1] + natural_pop + gain_pop * alloc[2]     # population
            new_metrics[2] = metrics[2] + gain_mil * alloc[0] - military_decay * metrics[2]  # military
            return new_metrics
        
        self.agent = update_country(self.agent, alloc_agent)
        self.opp1 = update_country(self.opp1, alloc_opp)
        self.opp2 = update_country(self.opp2, alloc_opp)
        
        # If all countries choose diplomacy, add bonus (e.g. trade benefits).
        if decision_agent == "diplomacy" and decision_opp1 == "diplomacy" and decision_opp2 == "diplomacy":
            self.agent[0] += diplomacy_bonus_econ
            self.agent[1] += diplomacy_bonus_pop
            self.opp1[0] += diplomacy_bonus_econ
            self.opp1[1] += diplomacy_bonus_pop
            self.opp2[0] += diplomacy_bonus_econ
            self.opp2[1] += diplomacy_bonus_pop
        
        # Simple war interaction: pairwise battles.
        steal_fraction = 0.1  # fraction to steal on win
        war_penalty_fraction = 0.05  # penalty if both war
        
        def simulate_war(att_decision, def_decision, attacker, defender):
            if att_decision == "war" and def_decision == "diplomacy":
                if attacker[2] > defender[2]:
                    steal_econ = steal_fraction * defender[0]
                    steal_pop = steal_fraction * defender[1]
                    attacker[0] += steal_econ
                    attacker[1] += steal_pop
                    defender[0] -= steal_econ
                    defender[1] -= steal_pop
                else:
                    loss_econ = steal_fraction * attacker[0]
                    loss_pop = steal_fraction * attacker[1]
                    attacker[0] -= loss_econ
                    attacker[1] -= loss_pop
            # If both choose war, both incur losses.
            if att_decision == "war" and def_decision == "war":
                attacker[0] -= war_penalty_fraction * attacker[0]
                attacker[1] -= war_penalty_fraction * attacker[1]
                defender[0] -= war_penalty_fraction * defender[0]
                defender[1] -= war_penalty_fraction * defender[1]
        
        # Agent interacts with both opponents.
        simulate_war(decision_agent, decision_opp1, self.agent, self.opp1)
        simulate_war(decision_agent, decision_opp2, self.agent, self.opp2)
        # Opponents also interact between themselves (affecting their own numbers).
        simulate_war(decision_opp1, decision_opp2, self.opp1, self.opp2)
        simulate_war(decision_opp2, decision_opp1, self.opp2, self.opp1)
        
        # Compute new totals.
        new_agent_total = self.agent.sum()
        new_opp_avg = (self.opp1.sum() + self.opp2.sum()) / 2.0
        # Reward is the change in the relative advantage.
        reward = (new_agent_total - new_opp_avg) - (old_agent_total - old_opp_avg)
        
        next_state = self._get_state()
        done = False  # Episodes can be terminated after fixed steps externally.
        info = {
            "agent_decision": decision_agent,
            "opp1_decision": decision_opp1,
            "opp2_decision": decision_opp2
        }
        return next_state, reward, done, info

# -----------------------------
# Main Training Loop using the CompetitionEnv
# -----------------------------
if __name__ == "__main__":
    env = CompetitionEnv()
    agent = DDPGAgent(state_dim=env.state_dim, action_dim=env.action_dim)
    
    num_episodes = 100
    max_steps = 50
    
    for episode in range(num_episodes):
        state = env.reset()
        episode_reward = 0
        for step in range(max_steps):
            action = agent.select_action(state)
            next_state, reward, done, info = env.step(action)
            agent.replay_buffer.push(state, action, reward, next_state, done)
            agent.update()
            state = next_state
            episode_reward += reward
            if done:
                break
        print(f"Episode {episode}, Reward: {episode_reward:.2f}, Info: {info}")
