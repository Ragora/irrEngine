#include <CLiquidBody.h>

CLiquidBody::CLiquidBody(IrrlichtDevice *device, irrBulletWorld *world)
{
    World = world;
    Device = device;
    setType(E_ENTITY_LIQUIDBODY);

    Body = World->addLiquidBody(vector3df(-5000,0,5000),irr::core::aabbox3df(0, -10000, 0, 10000, 0, 10000), 500.0f, 200.0f);
    Body->setCurrentDirection(vector3df(0,30,0));
    Body->setGlobalWaveChangeIncrement(0.01f);
    Body->setGlobalWaveUpdateFrequency(1.0f);
    Body->setMaxGlobalWaveHeight(4.0f);
    Body->setMinGlobalWaveHeight(-1.0f);
    Body->setLocalWaveValues(10,1,0.5f);
    Body->setInfinite(true);
    Body->setInfiniteDepth(true);
    Body->setLiquidDensity(0.1f);

    IAnimatedMesh* mesh = device->getSceneManager()->addHillPlaneMesh( "myHill",
		core::dimension2d<f32>(20,20),
		core::dimension2d<u32>(40,40), 0, 0,
		core::dimension2d<f32>(0,0),
		core::dimension2d<f32>(1000,1000));

	Node = device->getSceneManager()->addWaterSurfaceSceneNode(mesh->getMesh(0), 0.0f, 300.0f, 30.0f);
	Node->setPosition(core::vector3df(0,5,0));

	Node->setMaterialTexture(0, device->getVideoDriver()->getTexture("water.jpg"));
	Node->setMaterialFlag(EMF_LIGHTING, false);
	Node->setScale(vector3df(1000,1,1000));
}

CLiquidBody::~CLiquidBody()
{
    Node->remove();
}

void CLiquidBody::think()
{

}
