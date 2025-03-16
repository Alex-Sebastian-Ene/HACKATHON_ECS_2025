"use client";

import { useRouter } from "next/navigation";
import Map from "./UI/map";
import City from "./UI/city";

export default function Home() {
  const router = useRouter();
  return (
    <div className="bg-[url('/image/bg_1.jpg')] bg-cover w-full h-screen 2xl:w-auto">
      <header>
        <div className="absolute">
          <div className="flex flex-row items-left justify-center h-full">
            <div className="relative mt-[-25]">
              <img src="/image/scroll.png" alt="gold" className="w-80 h-40" />
              <div className="w-full absolute top-16 left-30 ">
                <p className="text-black text-3xl">Day 1</p>
              </div>
            </div>
            <div className="relative mx-2 mt-5">
              <img src="/image/gold.png" alt="gold" className="w-60 h-18" />
              <div className="w-full absolute top-6 left-23 ">
                <p className="text-white">1000</p>
              </div>
            </div>
            <div className="relative mx-2 mt-5">
              <img src="/image/steel.png" alt="steel" className="w-60 h-20" />
              <div className="w-full absolute top-6.5 left-25 ">
                <p className="text-white">1000</p>
              </div>
            </div>
            <div className="relative mx-5 mt-5">
              <img
                src="/image/popularity.png"
                alt="popularity"
                className="w-60 h-20"
              />
              <div className="w-full absolute top-7 left-22 ">
                <p className="text-white">1000</p>
              </div>
            </div>
            <div className="relative mx-5 mt-4">
              <img
                src="/image/happiness.png"
                alt="popularity"
                className="w-60 h-20"
              />
              <div className="w-full absolute top-8 left-20 ">
                <p className="text-white">1000</p>
              </div>
            </div>
          </div>
        </div>
      </header>
      <div className="absolute inset-y-0 right-0 items-right justify-center h-full">
        <div className="mt-5 mr-5">
          <button className="w-35 h-35">
            <img src="/image/research.png" alt="research" />
          </button>
        </div>
        <div className="mt-5">
          <button className="w-35 h-35">
            <img src="/image/food.png" alt="food" />
          </button>
        </div>
        <div className="mt-5">
          <button className="w-35 h-35">
            <img src="/image/relations.png" alt="relations" />
          </button>
        </div>
        <div className="mt-5">
          <button className="w-35 h-35">
            <img src="/image/military.png" alt="military" />
          </button>
        </div>
        <div className="mt-5">
          <button
            className="w-35 h-35"
            onClick={() => router.push("/technology")}
          >
            <img src="/image/technology.png" alt="technology" />
          </button>
        </div>
      </div>
      <Map />
    </div>
  );
}
