"use client";

import { useRouter } from "next/navigation";
import Map from "./UI/map";

export default function Home() {
  const router = useRouter();
  return (
    <div className="bg-[url('/image/bg_1.jpg')] bg-cover w-full h-screen 2xl:w-auto">
      <header>
        <div className="absolute">
          <div className="flex flex-col items-left justify-center h-full">
            <div className="relative mt-[-25]">
              <img src="/image/scroll.png" alt="gold" className="w-80 h-40" />
              <div className="w-full absolute top-16 left-30 ">
                <p className="text-black text-3xl">Day 1</p>
              </div>
            </div>
            <div className="grid grid-cols-2">
              <div className="relative mx-10">
                <img src="/image/12.png" alt="gold" className="w-60 h-18" />
                <div className="w-full absolute top-6 left-23 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/13.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/14.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/15.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/16.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/17.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/18.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/19.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/20.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/21.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/22.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/23.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/24.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/25.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/26.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/27.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
              </div>
              <div className="relative mx-10 mt-5">
                <img src="/image/28.png" alt="steel" className="w-60 h-18" />
                <div className="w-full absolute top-6.5 left-25 ">
                  <p className="text-white">1000</p>
                </div>
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
          <button
            className="w-35 h-35"
            onClick={() => router.push("/military")}
          >
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
