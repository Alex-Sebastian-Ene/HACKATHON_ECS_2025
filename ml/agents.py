import torch
import torch.nn as nn
import torch.optim as optim
import numpy as np
import random
from collections import deque

# -----------------------------
# Actor & Critic Networks
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
        # Bound the output between -1 and 1
        action = torch.tanh(self.fc3(x))
        return action

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
        q_value = self.fc3(x)
        return q_value

# -----------------------------
# Replay Buffer for Experience
# -----------------------------
class ReplayBuffer:
    def __init__(self, capacity):
        self.capacity = capacity
        self.buffer = deque(maxlen=capacity)
    
    def push(self, state, action, reward, next_state, done):
        self.buffer.append((state, action, reward, next_state, done))
    
    def sample(self, batch_size):
        batch = random.sample(self.buffer, batch_size)
        state, action, reward, next_state, done = map(np.stack, zip(*batch))
        return state, action, reward, next_state, done
    
    def __len__(self):
        return len(self.buffer)

# -----------------------------
# DDPG Agent
# -----------------------------
class DDPGAgent:
    def __init__(self, state_dim, action_dim, hidden_dim=256,
                 actor_lr=1e-3, critic_lr=1e-3, gamma=0.99, tau=0.005,
                 buffer_capacity=100000, batch_size=64):
        self.state_dim = state_dim
        self.action_dim = action_dim
        self.gamma = gamma
        self.tau = tau
        self.batch_size = batch_size

        # Actor and target actor
        self.actor = Actor(state_dim, action_dim, hidden_dim)
        self.actor_target = Actor(state_dim, action_dim, hidden_dim)
        self.actor_target.load_state_dict(self.actor.state_dict())
        self.actor_optimizer = optim.Adam(self.actor.parameters(), lr=actor_lr)

        # Critic and target critic
        self.critic = Critic(state_dim, action_dim, hidden_dim)
        self.critic_target = Critic(state_dim, action_dim, hidden_dim)
        self.critic_target.load_state_dict(self.critic.state_dict())
        self.critic_optimizer = optim.Adam(self.critic.parameters(), lr=critic_lr)

        self.replay_buffer = ReplayBuffer(buffer_capacity)
    
    def select_action(self, state, noise_scale=0.1):
        state = torch.FloatTensor(state).unsqueeze(0)
        action = self.actor(state).detach().numpy()[0]
        # Add Gaussian noise for exploration
        action = action + noise_scale * np.random.randn(self.action_dim)
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
        
        # Critic update using target networks
        with torch.no_grad():
            next_action = self.actor_target(next_state)
            target_q = self.critic_target(next_state, next_action)
            target_value = reward + (1 - done) * self.gamma * target_q
        
        current_q = self.critic(state, action)
        critic_loss = nn.MSELoss()(current_q, target_value)
        self.critic_optimizer.zero_grad()
        critic_loss.backward()
        self.critic_optimizer.step()
        
        # Actor update to maximize Q value
        actor_loss = -self.critic(state, self.actor(state)).mean()
        self.actor_optimizer.zero_grad()
        actor_loss.backward()
        self.actor_optimizer.step()
        
        # Soft update target networks
        for target_param, param in zip(self.actor_target.parameters(), self.actor.parameters()):
            target_param.data.copy_(target_param.data * (1-self.tau) + param.data * self.tau)
        for target_param, param in zip(self.critic_target.parameters(), self.critic.parameters()):
            target_param.data.copy_(target_param.data * (1-self.tau) + param.data * self.tau)

# -----------------------------
# Basic Environment Definition
# -----------------------------
class CountryEnv:
    """
    A dummy environment for a three-country game.
    State vector: [our_economy, our_population, our_military, opp1_military, opp2_military]
    Action: 1-dimensional continuous value, later interpreted as:
      >0: war, <=0: diplomacy
    """
    def __init__(self):
        self.state_dim = 5
        self.action_dim = 1
        self.reset()
    
    def reset(self):
        self.state = np.random.rand(self.state_dim)
        return self.state
    
    def step(self, action):
        our_decision = "war" if action[0] > 0 else "diplomacy"
        # Opponents randomly decide
        opponent1 = "war" if np.random.rand() > 0.5 else "diplomacy"
        opponent2 = "war" if np.random.rand() > 0.5 else "diplomacy"
        
        # Reward logic (can be expanded):
        # - If we go to war while at least one opponent is war, incur cost.
        # - If we are the only one at war, gain a small advantage.
        # - Mutual diplomacy yields cooperation bonus.
        if our_decision == "war":
            if opponent1 == "war" or opponent2 == "war":
                reward = -1.0  # high war cost if conflict is widespread
            else:
                reward = 1.0   # advantage if only we are aggressive
        else:  # diplomacy
            if opponent1 == "diplomacy" and opponent2 == "diplomacy":
                reward = 1.0  # cooperation
            else:
                reward = -0.5 # penalty if others are aggressive
        
        # For simplicity, new state is randomized; in a full simulation it would reflect strategic changes.
        next_state = np.random.rand(self.state_dim)
        done = False
        info = {"our_decision": our_decision,
                "opponent1": opponent1,
                "opponent2": opponent2}
        return next_state, reward, done, info

# -----------------------------
# Main Training Loop
# -----------------------------
if __name__ == "__main__":
    env = CountryEnv()
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
        print(f"Episode {episode}, Reward: {episode_reward}")
