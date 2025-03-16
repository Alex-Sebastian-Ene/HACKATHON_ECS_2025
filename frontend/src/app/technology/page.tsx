/* eslint-disable @next/next/no-img-element */
"use client";

import { useRouter } from "next/navigation";
import Techboard from "../UI/techboard";
import React from "react";
export default function Techonology() {
  const [showTechBoard, setShowTechBoard] = React.useState(false);
  const [skill, setSkill] = React.useState(0);
  const [tech, setTech] = React.useState(0);
  const [happiness, setHappiness] = React.useState(0);
  const [popularity, setPopularity] = React.useState(0);
  const [unrest, setUnrest] = React.useState(0);
  const [money, setMoney] = React.useState(0);
  const [metal, setMetal] = React.useState(0);
  const [wood, setWood] = React.useState(0);
  const [food, setFood] = React.useState(0);
  const [water, setWater] = React.useState(0);
  const [stone, setStone] = React.useState(0);
  const [manpower, setManpower] = React.useState(0);
  const [miliExp, setMiliExp] = React.useState(0);
  const [movement, setMovement] = React.useState(0);
  const [morale, setMorale] = React.useState(0);
  const [diseases, setDiseases] = React.useState(0);
  const [mortality, setMortatility] = React.useState(0);
  const onShow = () => setShowTechBoard(true);
  const resetVar = () => {
    setShowTechBoard(false);
    setDiseases(0);
    setFood(0);
    setHappiness(0);
    setManpower(0);
    setMetal(0);
    setMiliExp(0);
    setMoney(0);
    setMorale(0);
    setMovement(0);
    setPopularity(0);
    setStone(0);
    setTech(0);
    setUnrest(0);
    setWater(0);
    setWood(0);
    setMortatility(0);
  };
  const router = useRouter();
  return (
    <div className="bg-[url('/image/bg_2.jpg')] bg-cover w-full h-screen 2xl:w-auto overflow-hidden">
      <header>
        <div className="absolute items-left justify-center">
          <div className="mr-5">
            <button className="w-35 h-35" onClick={() => router.push("/")}>
              <img src="/image/back.png" alt="back" />
            </button>
          </div>
        </div>
      </header>
      <div className="absolute top-[25%] left-[45%] z-70">
        {showTechBoard ? (
          <Techboard
            skill={skill}
            tech={tech}
            happiness={happiness}
            popularity={popularity}
            unrest={unrest}
            money={money}
            metal={metal}
            wood={wood}
            food={food}
            water={water}
            stone={stone}
            manpower={manpower}
            miliExp={miliExp}
            movement={movement}
            morale={morale}
            diseases={diseases}
            mortality={mortality}
            setShowTechBoard={setShowTechBoard}
          />
        ) : null}
      </div>
      <div className="absolute top-[40%] left-[5%] overflow-hidden w-70 h-70">
        <div className="relative">
          <button
            onClick={() => {
              resetVar();
              onShow();
              setSkill(1);
              setHappiness(10);
              setUnrest(-10);
            }}
          >
            <img src="/image/skill_point.png" alt="skill_1" />
          </button>
        </div>
      </div>
      <div className="fixed top-[60%] left-[13%] w-70 h-70">
        <div className="relative">
          <button
            onClick={() => {
              resetVar();
              onShow();
              console.log("skill 2");
              setSkill(2);
              setMoney(10000);
              setUnrest(-10);
            }}
          >
            <img
              src="/image/skill_point.png"
              alt="skill_1"
              className="pointer-events-none z-0"
            />
          </button>
        </div>
      </div>
      <div className="fixed top-[73%] left-[23%] w-70 h-70 z-0">
        <button
          onClick={() => {
            resetVar();
            onShow();
            setSkill(3);
            setMiliExp(+50);
            setUnrest(-10);
          }}
        >
          <img src="/image/skill_point.png" alt="skill_1" />
        </button>
      </div>
      <div className="fixed top-[20%] left-[15%] w-70 h-70 z-0">
        <button
          onClick={() => {
            resetVar();
            onShow();
            setSkill(9);
            setPopularity(1000);
            setManpower(100);
          }}
        >
          <img src="/image/skill_point.png" alt="skill_1" />
        </button>
      </div>
      <div className="fixed top-[40%] left-[17%] w-70 h-70 z-0">
        <button
          onClick={() => {
            resetVar();
            onShow();
            setSkill(4);
            setWater(1000);
            setFood(1000);
          }}
        >
          <img src="/image/skill_point.png" alt="skill_1" />
        </button>
      </div>
      <div className="fixed top-[70%] left-[37%] w-70 h-70 z-0">
        <button
          onClick={() => {
            resetVar();
            onShow();
            setSkill(7);
            setFood(1000);
            setMortatility(-10);
          }}
        >
          <img src="/image/skill_point.png" alt="skill_1" />
        </button>
      </div>
      <div className="fixed top-[83%] left-[60%] w-70 h-70 z-0">
        <button
          onClick={() => {
            resetVar();
            onShow();
            setSkill(8);
            setMovement(50);
          }}
        >
          <img src="/image/skill_point.png" alt="skill_1" />
        </button>
      </div>
      <div className="fixed top-[35%] left-[36%] w-70 h-70 z-0">
        <button
          onClick={() => {
            resetVar();
            onShow();
            setSkill(5);
            setMetal(1000);
            setMoney(1000);
          }}
        >
          <img src="/image/skill_point.png" alt="skill_1" />
        </button>
      </div>
      <div className="fixed top-[45%] left-[57%] w-70 h-70 z-0">
        <button
          onClick={() => {
            resetVar();
            onShow();
            setSkill(6);
            setWood(1000);
          }}
        >
          <img src="/image/skill_point.png" alt="skill_1" />
        </button>
      </div>
      <div className="fixed top-[60%] left-[67%] w-70 h-70 z-0">
        <button
          onClick={() => {
            resetVar();
            onShow();
            setSkill(10);
            setTech(100);
          }}
        >
          <img src="/image/skill_point.png" alt="skill_1" />
        </button>
      </div>
      <div className="fixed top-[74%] left-[77%] w-70 h-70 z-0">
        <button
          onClick={() => {
            resetVar();
            onShow();
            setSkill(11);
            setMiliExp(100);
            setTech(50);
          }}
        >
          <img src="/image/skill_point.png" alt="skill_1" />
        </button>
      </div>
      <div className="fixed top-[3%] left-[26%] w-70 h-70 z-0">
        <button
          onClick={() => {
            resetVar();
            onShow();
            setSkill(12);
            setMorale(100);
            setManpower(100);
          }}
        >
          <img src="/image/skill_point.png" alt="skill_1" />
        </button>
      </div>
      <div className="fixed top-[1%] left-[48%] w-70 h-70 z-0">
        <button
          onClick={() => {
            resetVar();
            onShow();
            setSkill(13);
            setDiseases(-100);
            setMortatility(-100);
          }}
        >
          <img src="/image/skill_point.png" alt="skill_1" />
        </button>
      </div>
      <div className="fixed left-[67%] w-70 h-70 z-0">
        <button
          onClick={() => {
            resetVar();
            onShow();
            setSkill(14);
            setPopularity(100);
            setMortatility(-100);
          }}
        >
          <img src="/image/skill_point.png" alt="skill_1" />
        </button>
      </div>
      <div className="fixed top-[40%] left-[69%] w-70 h-70 z-0">
        <button
          onClick={() => {
            resetVar();
            onShow();
            setSkill(15);
            setMiliExp(150);
            setMorale(100);
          }}
        >
          <img src="/image/skill_point.png" alt="skill_1" />
        </button>
      </div>
    </div>
  );
}
