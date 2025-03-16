import React from "react";
interface FightProps {
  countryName: string;
  setShowFight: React.Dispatch<React.SetStateAction<boolean>>;
}
const Fight: React.FC<FightProps> = ({ countryName, setShowFight }) => {
  return (
    <div className="flex items-top justify-center h-2/3 w-1/2 z-30 overflow-hidden">
      <img src="/image/tech_board.png" alt="tech_board" />
      <div className="absolute mt-30 mx-5 ">
        <div className="flex flex-col space-y-5 items-center">
          <img src="/image/militaryIcon.png" alt="mili" className="w-70 h-60" />
          <div className="text-center text-white text-3xl font-bold mb-10 mx-10">
            {countryName}
          </div>
          <button className="w-[80%]">
            <img
              src="/image/attack_city.png"
              alt="close"
              onClick={() => setShowFight(false)}
            />
          </button>
          <button className="w-[80%]">
            <img
              src="/image/negotiate.png"
              alt="close"
              onClick={() => setShowFight(false)}
            />
          </button>
          <button>
            <img
              src="/image/close.png"
              alt="close"
              onClick={() => setShowFight(false)}
            />
          </button>
        </div>
      </div>
    </div>
  );
};
export default Fight;
