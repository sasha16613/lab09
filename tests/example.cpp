// Copyright 2022 nikolay.sasha@mail.ru
//

#include <gtest/gtest.h>

#include <example.hpp>

TEST(Resistor, CalculatesResistance) {
  float resistance = 27.;

  Resistor r(resistance);
  Power p;

  float actualResistance = r.CalculateResistance(p);

  EXPECT_EQ(resistance, actualResistance);
}

TEST(Resistor, SenqualConnection) {
  float resistance1 = 27.;
  float resistance2 = 33.;

  auto* r1 = new Resistor(resistance1);
  auto* r2 = new Resistor(resistance2);
  Power p;

  SequentialConnections c;
  c.addElements(r1);
  c.addElements(r2);

  float actualResistance = c.CalculateResistance(p);

  EXPECT_FLOAT_EQ(60., actualResistance);
  delete r1;
  delete r2;
}

TEST(Resistor, ParallelConnection) {
  float resistance1 = 27.;
  float resistance2 = 33.;

  auto* r1 = new Resistor(resistance1);
  auto* r2 = new Resistor(resistance2);
  Power p;

  ParallelConnections c;
  c.addElements(r1);
  c.addElements(r2);
  float actualResistance = c.CalculateResistance(p);

  EXPECT_FLOAT_EQ(14.85, actualResistance);
  delete r1;
  delete r2;
}

TEST(Capacitor, CalculatesResistance) {
  float capacity = 27.;

  Capacitor r(capacity);
  Power p;

  float actualResistance = r.CalculateResistance(p);

  EXPECT_EQ((float)(1 / (2 * 3.14 * 60 * capacity)), actualResistance);
}

TEST(Inductor, CalculatesResistance) {
  float induction = 27.;

  Inductor r(induction);
  Power p;

  float actualResistance = r.CalculateResistance(p);

  EXPECT_EQ(60 * induction, actualResistance);
}

TEST(All, Combination) {
  float capasitor = 12.;
  float resistor = 27.;
  float inductor = 7.;
  auto* c1 = new Capacitor(capasitor);
  auto* r1 = new Resistor(resistor);
  auto* i1 = new Inductor(inductor);
  Power p;

  SequentialConnections sc;
  sc.addElements(c1);
  sc.addElements(r1);
  ParallelConnections pc;
  pc.addElements(i1);
  auto* all = new Combined(pc);
  pc.addElements(all);
  EXPECT_FLOAT_EQ(209.99998, pc.CalculateResistance(p));
  delete r1;
  delete c1;
  delete i1;
  delete all;
}
