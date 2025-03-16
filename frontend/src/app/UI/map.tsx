/* eslint-disable @next/next/no-img-element */
import React from "react";
import City from "./city";
const Map: React.FC = () => {
  const [showCity, setShowCity] = React.useState(false);
  const [city, setCity] = React.useState("");
  return (
    <div className="flex items-center justify-center h-full overflow-hidden">
      {showCity ? <City cityName={city} setShowCity={setShowCity} /> : null}
      <img
        src="/image/map.png"
        alt="map"
        className="absolute mr-20 w-3/5 2xl:w-1/2 "
      />
      <button
        className="absolute top-[78%] left-[63%] w-20 h-20"
        onClick={() => {
          setShowCity(true);
          setCity("Guangzhou");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Guangzhou</p>
      </button>
      <button
        className="absolute top-[70%] left-[57%] w-20 h-20"
        onClick={() => {
          setShowCity(true);
          setCity("Yizhou");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Yizhou</p>
      </button>
      <button
        className="absolute top-[60%] left-[59%] w-20 h-20"
        onClick={() => {
          setShowCity(true);
          setCity("Chang'an");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Chang'an</p>
      </button>
      <button
        className="absolute top-[50%] left-[54%] w-20 h-20"
        onClick={() => {
          setShowCity(true);
          setCity("Shanzhou");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Shanzhou</p>
      </button>
      <button
        className="absolute top-[57%] left-[63%] w-20 h-20"
        onClick={() => {
          setShowCity(true);
          setCity("Bianzhou");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Bianzhou</p>
      </button>
      <button
        className="absolute top-[40%] left-[48%] w-20 h-20"
        onClick={() => {
          setShowCity(true);
          setCity("Tingzhou");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Tingzhou</p>
      </button>
      <button
        className="absolute top-[42%] left-[40%] w-20 h-20"
        onClick={() => {
          setShowCity(true);
          setCity("Shule");
        }}
      >
        <img src="/image/flag.png" alt="flag" />
        <p className="text-white font-bold">Shule</p>
      </button>
      <button
        className="absolute top-[30%] left-[55%] w-50 h-50"
        onClick={() => {
          setShowCity(true);
          setCity("Tujue");
        }}
      >
        <p className="text-white font-bold text-5xl">Tujue</p>
      </button>
      <button
        className="absolute top-[62%] left-[45%] w-50 h-50"
        onClick={() => {
          setShowCity(true);
          setCity("Tu'bo");
        }}
      >
        <p className="text-white font-bold text-5xl">Tu'bo</p>
      </button>
    </div>
  );
};
export default Map;
