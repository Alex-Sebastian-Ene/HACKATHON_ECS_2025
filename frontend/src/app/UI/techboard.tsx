import React from "react";
interface TechboardProps {
  skill: number;
  tech: number;
  happiness: number;
  popularity: number;
  unrest: number;
  money: number;
  metal: number;
  wood: number;
  food: number;
  water: number;
  stone: number;
  manpower: number;
  miliExp: number;
  movement: number;
  morale: number;
  diseases: number;
  mortality: number;
  setShowTechBoard: React.Dispatch<React.SetStateAction<boolean>>;
}
const Techboard: React.FC<TechboardProps> = ({
  skill,
  tech,
  happiness,
  popularity,
  unrest,
  money,
  metal,
  wood,
  food,
  water,
  stone,
  manpower,
  miliExp,
  movement,
  morale,
  diseases,
  mortality,
  setShowTechBoard,
}) => {
  const skillList = [
    "New Chess Game Being Popular",
    "Establish Export Of Metal",
    "Send More Soldiers To Garriso The Frontiers",
    "New Irrigation Ditch Built",
    "New Metal Mine",
    "Employ More People To Deforest",
    "Collect Crops From Arms To Central",
    "Built New Roads Between Cities",
    "Sponsor For Extra Kid At Home",
    "Build 3 New Schools",
    "Establish Tratical Drills",
    "Rewards Given to Soldiers/Workers",
    "Build New Hospitals",
    "New Medicine Discovered",
    "Win A War Against Neighbouring Country",
  ];
  const [available, setAvailable] = React.useState(1);
  const checkAvailable = (skill: number) => {};
  return (
    <div className="flex items-top justify-center h-full overflow-hidden">
      <img src="/image/tech_board.png" alt="tech_board" />
      <div className="absolute mt-30 mx-5 ">
        <div className="flex flex-col space-y-5 items-center">
          <img src="/image/tech.png" alt="tech" className="w-40 h-40" />
          <div className="text-center text-white text-2xl font-bold mb-10 mx-10">
            {skillList[skill - 1]}
          </div>
          {tech != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Tech: {tech}
            </div>
          ) : null}
          {happiness != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Happiness: {happiness}
            </div>
          ) : null}
          {popularity != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Popularity: {popularity}
            </div>
          ) : null}
          {unrest != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Unrest: {unrest}
            </div>
          ) : null}
          {money != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Money: {money}
            </div>
          ) : null}
          {metal != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Metal: {metal}
            </div>
          ) : null}
          {wood != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Wood: {wood}
            </div>
          ) : null}
          {food != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Food: {food}
            </div>
          ) : null}
          {water != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Water: {water}
            </div>
          ) : null}
          {stone != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Stone: {stone}
            </div>
          ) : null}
          {manpower != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Manpower: {manpower}
            </div>
          ) : null}
          {miliExp != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Military Experience: {miliExp}
            </div>
          ) : null}
          {movement != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Movement: {movement}
            </div>
          ) : null}
          {morale != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Morale: {morale}
            </div>
          ) : null}
          {diseases != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Diseases Rate: {diseases}
            </div>
          ) : null}
          {mortality != 0 ? (
            <div className="mx-10 text-white text-xl font-bold">
              Mortality: {mortality}
            </div>
          ) : null}
          {available == 0 ? (
            <div className="mx-10 text-white text-center text-xl">
              Must unlock previous skill first
            </div>
          ) : null}
          {available == 1 ? (
            <div className="flex flex-col items-center justify-center">
              <button onClick={() => setShowTechBoard(false)}>
                <img src="/image/tech_button.png" alt="tech_button" />
              </button>
              <div className="mx-10 text-white text-center text-xl">
                Money Required: 1000
              </div>
            </div>
          ) : null}
          {available == 2 ? (
            <div className="mx-10 text-white text-center text-xl">
              Technology Unlocked Already
            </div>
          ) : null}
        </div>
      </div>
    </div>
  );
};
export default Techboard;
