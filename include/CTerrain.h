#ifndef _CTerrain
#define _CTerrain

#include <irrlicht.h>

using namespace irr;

//#pragma comment(lib, "Irrlicht.lib")

class CTerrain : public scene::ISceneNode
{
    public:
        const enum TerrainQuality {High=1,Medium=2,Low=4,ExtraLow=8};
        CTerrain::CTerrain(c8* HeightmapFile,TerrainQuality Quality,f32 ScaleTexture,scene::ISceneNode* parent,scene::ISceneManager* smgr,s32 id);
        CTerrain::~CTerrain();
        void setColorTexture(c8* FileName);
        void setDetailTexture(c8* FileName);
        void SetTextureSplat(u32 NumTex,c8* FileName);
        void setDebugMode(bool Enable);
        void setRenderDistance(f32 Distance);
        void ActivateSplattingTextures(scene::ISceneManager* smgr,f32 Height,f32 Fog,video::SColorf FogColor);
        scene::IMesh* getMesh();
        f32 getHeight(f32 x,f32 z);
        virtual void setMaterialType(const video::E_MATERIAL_TYPE Mat);
        virtual void OnRegisterSceneNode();
        virtual void render();
        virtual const core::aabbox3d<f32>& getBoundingBox() const;
        virtual video::SMaterial& getMaterial(u32 i);
        virtual void setPosition(const core::vector3df &Pos);
        virtual void setScale(const core::vector3df &Scale);
        u32 getMaterialCount();
    private:
        core::aabbox3d<f32> Box;
        video::SMaterial Material;
        scene::SMeshBufferLightMap** CTTileBuffer;
        void calculateNormals ( scene::SMeshBufferLightMap* pMeshBuffer,s32 Size);
        bool Debug;
        f32 RenderDistance;
        scene::SMesh* TerrainMesh;
        u16 NbsTiles;
};

class MyShaderCallBack : public video::IShaderConstantSetCallBack
{
public:
    scene::ISceneManager* smgr;
    f32 Height,Fog;
    video::SColorf FogColor;

    void setSplatScene(scene::ISceneManager* Scene,f32 height,f32 fog,video::SColorf fogColor)
    {
        smgr=Scene;
        Height = height;
        Fog = fog;
        FogColor = fogColor;
    }

    virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
    {
        video::IVideoDriver* driver = services->getVideoDriver();

        core::matrix4 worldViewProj;
        worldViewProj  = driver->getTransform(video::ETS_PROJECTION);
        worldViewProj *= driver->getTransform(video::ETS_VIEW);
        worldViewProj *= driver->getTransform(video::ETS_WORLD);

        if (driver->getDriverType() == video::EDT_OPENGL)
        {
            worldViewProj = worldViewProj.getTransposed();

            int var;
            var = 0;
            services->setPixelShaderConstant("texgrass", reinterpret_cast<f32*>(&var), 1);
            var = 1;
            services->setPixelShaderConstant("texrock", reinterpret_cast<f32*>(&var), 1);
            var = 2;
            services->setPixelShaderConstant("texsnow", reinterpret_cast<f32*>(&var), 1);
            var = 3;
            services->setPixelShaderConstant("texdetail", reinterpret_cast<f32*>(&var), 1);
        }
        services->setVertexShaderConstant("mWorldViewProj",worldViewProj.pointer(),16);

        services->setVertexShaderConstant("TerrainHeight",reinterpret_cast<f32*>(&Height),1);
        services->setVertexShaderConstant("FogDistance",reinterpret_cast<f32*>(&Fog),1);

        core::vector3df pos = smgr->getActiveCamera()->getPosition();
        services->setVertexShaderConstant("cameraPos", reinterpret_cast<f32*>(&pos), 3);

        core::matrix4 world = driver->getTransform(video::ETS_WORLD);
        services->setVertexShaderConstant("mWorld",world.pointer(),16);

        services->setPixelShaderConstant("fog",reinterpret_cast<f32*>(&FogColor),4);
    }
};

#endif
