/* eslint-disable @next/next/no-img-element */
import React from "react";
import Fight from "./fight";
import Army from "./army";
const MilitaryComponent: React.FC = () => {
  const [showFight, setShowFight] = React.useState(false);
  const [showArmy, setShowArmy] = React.useState(false);
  const [city, setCity] = React.useState("");
  const [country, setCountry] = React.useState("");
  return (
    <div className="flex items-center justify-center h-full overflow-hidden">
      {showFight ? (
        <Fight countryName={country} setShowFight={setShowFight} />
      ) : null}
      {showArmy ? <Army cityName={city} setShowArmy={setShowArmy} /> : null}
      <img
        src="/image/map.png"
        alt="map"
        className="absolute mr-20 w-3/5 2xl:w-1/2 "
      />
      <button
        className="absolute top-[80%] left-[76%] w-20 h-20"
        onClick={() => {
          setShowFight(false);
          setShowArmy(true);
          setCity("Guangzhou");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Guangzhou</p>
      </button>
      <button
        className="absolute top-[72%] left-[70%] w-20 h-20"
        onClick={() => {
          setShowFight(false);
          setShowArmy(true);
          setCity("Yizhou");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Yizhou</p>
      </button>
      <button
        className="absolute top-[60%] left-[72%] w-20 h-20"
        onClick={() => {
          setShowFight(false);
          setShowArmy(true);
          setCity("Chang'an");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Chang'an</p>
      </button>
      <button
        className="absolute top-[52%] left-[67%] w-20 h-20"
        onClick={() => {
          setShowFight(false);
          setShowArmy(true);
          setCity("Shanzhou");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Shanzhou</p>
      </button>
      <button
        className="absolute top-[58%] left-[76%] w-20 h-20"
        onClick={() => {
          setShowFight(false);
          setShowArmy(true);
          setCity("Bianzhou");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Bianzhou</p>
      </button>
      <button
        className="absolute top-[40%] left-60%] w-20 h-20"
        onClick={() => {
          setShowFight(false);
          setShowArmy(true);
          setCity("Tingzhou");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Tingzhou</p>
      </button>
      <button
        className="absolute top-[42%] left-[50%] w-20 h-20"
        onClick={() => {
          setShowFight(false);
          setShowArmy(true);
          setCity("Shule");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Shule</p>
      </button>
      <button
        className="absolute top-[30%] left-[67%] w-50 h-50"
        onClick={() => {
          setShowFight(true);
          setShowArmy(false);
          setCountry("Tujue");
        }}
      >
        <p className="text-white font-bold text-5xl">Tujue</p>
      </button>
      <button
        className="absolute top-[62%] left-[58%] w-50 h-50"
        onClick={() => {
          setShowFight(true);
          setShowArmy(false);
          setCity("Tu'bo");
        }}
      >
        <p className="text-white font-bold text-5xl">Tu'bo</p>
      </button>
    </div>
  );
};
export default MilitaryComponent;
