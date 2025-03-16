/* eslint-disable @next/next/no-img-element */
"use client";

import { useRouter } from "next/navigation";
import MilitaryComponent from "../UI/military";
export default function Military() {
  const router = useRouter();
  return (
    <div className="bg-[url('/image/bg_2.jpg')] bg-cover w-full h-screen xl:w-auto overflow-hidden">
      <header>
        <div className="absolute items-left justify-center">
          <div className="mr-5">
            <button className="w-35 h-35" onClick={() => router.push("/")}>
              <img src="/image/back.png" alt="back" />
            </button>
          </div>
        </div>
      </header>
      <div className="flex flex-row ">
        <div className="relative w-1/2 mt-20">
          <img src="/image/miliExp.png" className="w-3/4 h-[90%]" />
          <div className="w-full absolute top-[30%] left-[20%] space-y-10">
            <p className="text-black text-xl">
              <b>Last day since war:</b> last_day_since_war
            </p>
            <p className="text-black text-xl ">
              <b>Wars fought:</b> wars_fought
            </p>
            <p className="text-black text-xl">
              <b>Wars won:</b> wars_won
            </p>
            <p className="text-black text-xl">
              <b>Wars Lost:</b> wars_lost
            </p>
            <p className="text-black text-xl">
              <b>Military Experience:</b> military_experience
            </p>
            <p className="text-black text-xl">
              <b>Military Power:</b> military_power
            </p>
            <p className="text-black text-xl">
              <b>Military Technology:</b> military_technology
            </p>
            <p className="text-black text-xl">
              <b>Readiness:</b> readiness
            </p>
          </div>
        </div>
        <div className="w-1/4 mb-20">
          <MilitaryComponent />
        </div>
      </div>
    </div>
  );
}
