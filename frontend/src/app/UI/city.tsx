import React from "react";
interface CityProps {
  cityName: string;
  setShowCity: React.Dispatch<React.SetStateAction<boolean>>;
}
const City: React.FC<CityProps> = ({ cityName, setShowCity }) => {
  return (
    <div className="flex items-top justify-center h-1/2 z-10 overflow-hidden">
      <img src="/image/city.png" alt="city" />
      <div className="absolute mt-30 mx-5 ">
        <div className="flex flex-col space-y-5 items-center">
          <div className="text-center text-white text-4xl font-bold mb-10 mx-10">
            {cityName}
          </div>
        </div>
        <div className="items-right justify-right h-full ml-60 mt-20">
          <div className="text-white text-2xl mb-10 mx-10">population</div>
        </div>
        <div className="items-right justify-right h-full ml-60 mt-40">
          <div className="text-white text-2xl mb-10 mx-10">army</div>
        </div>
        <div className="flex items-center justify-center h-full mt-25">
          <button>
            <img
              src="/image/close.png"
              alt="close"
              onClick={() => setShowCity(false)}
            />
          </button>
        </div>
      </div>
    </div>
  );
};
export default City;
