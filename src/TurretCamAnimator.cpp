#include "TurretCamAnimator.hpp"

using namespace irr;

TurretCamAnimator::TurretCamAnimator(scene::ISceneNode *_parent)
    : ISceneNodeAnimator()
    , parent(_parent)
{

}

TurretCamAnimator::~TurretCamAnimator()
{

}

void TurretCamAnimator::animateNode(scene::ISceneNode* node, u32)
{
    if (!parent || !node)
        return;

    parent->updateAbsolutePosition();
    core::vector3df nodeUpVector, nodeTarget;
    const core::matrix4& absTrans = parent->getAbsoluteTransformation();
    absTrans.rotateVect(nodeUpVector, core::vector3df(0.f, 1.f, 0.f));
    absTrans.transformVect(nodeTarget, core::vector3df(0.f, 0.f, 100.f));

    node->setPosition(parent->getAbsolutePosition() + core::vector3df(0.f, 1.75f, 0.f));
    if (node->getType() == scene::ESNT_CAMERA)
    {
        static_cast<scene::ICameraSceneNode*>(node)->setUpVector(nodeUpVector);
        static_cast<scene::ICameraSceneNode*>(node)->setTarget(nodeTarget);
    }
}
