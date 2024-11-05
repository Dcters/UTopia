/*****************************************************************************
*                 .::::.
*             ..:::...::::..
*         ..::::..      ..::::.
*      ..:::..              ..:::..
*   .::::.                      .::::.
*  .::.                            .::.
*  .::                         ..:. ::.  UTopia
*  .:: .::.                ..::::: .::.  Unit Tests to Fuzzing
*  .:: .:::             .::::::..  .::.  https://github.com/Samsung/UTopia
*  .:: .:::            ::::...     .::.
*  .:: .:::      ...   .....::     .::.  Base UT: ContactConstraint_ContactWithKinematicJoint_Test
*  .:: .:::      .::.  ..::::.     .::.
*  .:: .::: .:.  .:::  :::..       .::.  This file was generated automatically
*  .::. ... .::: .:::  ....        .::.  by UTopia v.0.2.0
*   .::::..  .:: .:::  .:::    ..:::..
*      ..:::...   :::  ::.. .::::..
*          ..:::.. ..  ...:::..
*             ..::::..::::.
*                 ..::..
*****************************************************************************/
#include "TestHelpers.hpp"
#include "dart/common/common.hpp"
#include "dart/constraint/constraint.hpp"
#include "dart/dynamics/dynamics.hpp"
#include "autofuzz.h"
#ifdef __cplusplus
extern "C" {
#endif
extern dart::dynamics::Joint::ActuatorType autofuzz0;
extern std::size_t autofuzz1;
extern double autofuzz2;
extern dart::dynamics::Joint::ActuatorType autofuzz3;
extern std::size_t autofuzz4;
extern double autofuzz5;
extern std::size_t autofuzz6;
extern double autofuzz7;
#ifdef __cplusplus
}
#endif
/*
 * Copyright (c) 2011-2024, The DART development contributors
 * All rights reserved.
 *
 * The list of contributors can be found at:
 *   https://github.com/dartsim/dart/blob/main/LICENSE
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#include "TestHelpers.hpp"
#include "dart/common/common.hpp"
#include "dart/constraint/constraint.hpp"
#include "dart/dynamics/dynamics.hpp"
#include "dart/simulation/World.hpp"

#include <gtest/gtest.h>

using namespace dart;

//==============================================================================
void testContactWithKinematicJoint(
    const constraint::BoxedLcpSolverPtr& lcpSolver, double tol)
{
  auto world = std::make_shared<simulation::World>();
  world->setConstraintSolver(
      std::make_unique<constraint::BoxedLcpConstraintSolver>(lcpSolver));

  auto skeleton1 = dynamics::Skeleton::create("skeleton1");
  auto pair1 = skeleton1->createJointAndBodyNodePair<dynamics::FreeJoint>();
  auto bodyNode1 = pair1.second;
  auto joint1 = pair1.first;
  joint1->setActuatorType(autofuzz0);
  auto shape1
      = std::make_shared<dynamics::BoxShape>(Eigen::Vector3d(1.0, 1.0, 1.0));
  bodyNode1->createShapeNodeWith<VisualAspect, CollisionAspect, DynamicsAspect>(
      shape1);
  skeleton1->setPosition(autofuzz1, autofuzz2);

  auto skeleton2 = dynamics::Skeleton::create("skeleton2");
  auto pair2 = skeleton2->createJointAndBodyNodePair<dynamics::FreeJoint>();
  auto bodyNode2 = pair2.second;
  auto joint2 = pair2.first;
  joint2->setActuatorType(autofuzz3);
  auto shape2
      = std::make_shared<dynamics::BoxShape>(Eigen::Vector3d(0.5, 0.5, 0.5));
  bodyNode2->createShapeNodeWith<VisualAspect, CollisionAspect, DynamicsAspect>(
      shape2);
  skeleton2->setPosition(autofuzz4, autofuzz5);

  world->addSkeleton(skeleton1);
  world->addSkeleton(skeleton2);

  for (auto i = 0u; i < 100; ++i) {
    skeleton1->setCommand(autofuzz6, autofuzz7);

    world->step();

    EXPECT_EQ(bodyNode1->getLinearVelocity()[0], 0.1);

    // Need few steps to settle down
    if (i > 15) {
      EXPECT_NEAR(bodyNode2->getLinearVelocity()[0], 0.1, tol);
    }
  }
}

//==============================================================================
TEST(ContactConstraint, ContactWithKinematicJoint)
{
  testContactWithKinematicJoint(
      std::make_shared<constraint::DantzigBoxedLcpSolver>(), 1e-6);

#ifdef DART_ARCH_32BITS
  testContactWithKinematicJoint(
      std::make_shared<constraint::PgsBoxedLcpSolver>(), 1e-3);
#else
  testContactWithKinematicJoint(
      std::make_shared<constraint::PgsBoxedLcpSolver>(), 1e-4);
#endif
}

#ifdef __cplusplus
extern "C" {
#endif
void enterAutofuzz() {
  class AutofuzzTest : public ContactConstraint_ContactWithKinematicJoint_Test {
  public:
    void runTest() {
      try {
        SetUpTestCase();
      } catch (std::exception &E) {}
      try {
        SetUp();
      } catch (std::exception &E) {}
      try {
        TestBody();
      } catch (std::exception &E) {}
      try {
        TearDown();
      } catch (std::exception &E) {}
      try {
        TearDownTestCase();
      } catch (std::exception &E) {}
    }
  };
  AutofuzzTest Fuzzer;
  Fuzzer.runTest();
}
#ifdef __cplusplus
}
#endif