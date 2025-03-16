import React from "react";
interface CityProps {
  cityName: string;
  setShowArmy: React.Dispatch<React.SetStateAction<boolean>>;
}
const Army: React.FC<CityProps> = ({ cityName, setShowArmy }) => {
  return (
    <div className="flex items-top justify-center h-2/3 w-1/2 z-30 overflow-hidden">
      <img src="/image/tech_board.png" alt="tech_board" />
      <div className="absolute mt-30 mx-5 ">
        <div className="flex flex-col space-y-5 items-center">
          <img src="/image/militaryIcon.png" alt="mili" className="w-70 h-60" />
          <div className="text-center text-white text-3xl font-bold mb-10 mx-10">
            {cityName}
          </div>
          <button className="w-[80%]">
            <img
              src="/image/Reinforce.png"
              alt="close"
              onClick={() => setShowArmy(false)}
            />
          </button>
          <button className="w-[80%]">
            <img
              src="/image/Garrison.png"
              alt="close"
              onClick={() => setShowArmy(false)}
            />
          </button>
          <button>
            <img
              src="/image/close.png"
              alt="close"
              onClick={() => setShowArmy(false)}
            />
          </button>
        </div>
      </div>
    </div>
  );
};
export default Army;
