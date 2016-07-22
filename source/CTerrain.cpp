#include <CTerrain.h>
#include <irrlicht.h>

using namespace irr;

CTerrain::CTerrain(c8* HeightmapFile,TerrainQuality Quality,f32 ScaleTexture,scene::ISceneNode* parent,scene::ISceneManager* smgr,s32 id): scene::ISceneNode(parent, smgr, id)
{
    //Test if the number of quality is correct
    if(Quality != 1 && Quality != 2 && Quality != 4 && Quality != 8)
    {
        //if not force to medium quality
        Quality = Medium;
    }

    //Set the Debug to false
    Debug=false;

    //Get the Heightmap
    video::IImage *Heightmap = SceneManager->getVideoDriver()->createImageFromFile(HeightmapFile);

    //Get dimension of heightmap
    u16 Size = Heightmap->getDimension().Width;

    //Set the size of Tiles for Terrain
    s32 SizeOfTiles = 0;

    //Switch Size for calculate the Size of Tile
    switch(Size)
    {
        case 64:
            SizeOfTiles=(Size/4)+1;
            NbsTiles = 4*4;
            break;
        case 128 :
            SizeOfTiles=(Size/8)+1;
            NbsTiles = 8*8;
            break;
        case 256 :
            SizeOfTiles=(Size/16)+1;
            NbsTiles = 16*16;
            break;
        case 512 :
            SizeOfTiles=(Size/16)+1;
            NbsTiles = 16*16;
            break;
        case 768 :
            SizeOfTiles=(Size/24)+1;
            NbsTiles = 24*24;
            break;
        case 1024:
            SizeOfTiles=(Size/32)+1;
            NbsTiles = 32*32;
            break;
        case 2048:
            SizeOfTiles=(Size/32)+1;
            NbsTiles = 32*32;
            break;
        default:
            SizeOfTiles=(Size/16)+1;
            NbsTiles = 16*16;
            break;
    }

    //Create the Mesh for the Terrain Mesh
    TerrainMesh = new scene::SMesh();

    //Calculate the quality factor
    u32 SOTiles = irr::core::ceil32((f32)SizeOfTiles/(f32)Quality);

    //Init the array of MeshBuffer
    CTTileBuffer=new scene::SMeshBufferLightMap* [NbsTiles];

    //Start the loop to create Buffers
    u32 TileX=0,TileZ=0;
    for (u32 i =0;i < NbsTiles;++i)
    {
        CTTileBuffer[i]=new scene::SMeshBufferLightMap();
        CTTileBuffer[i]->Vertices.set_used(SizeOfTiles*SizeOfTiles);
        CTTileBuffer[i]->Indices.set_used(SizeOfTiles*SizeOfTiles*6);

        const f32 tdSize = 1.0f/(f32)(Size-1);
        u32 Index=0;
        u16 NbsIndices=0,NbsVertices=0;

        for(u32 x=TileX;x<(TileX+SizeOfTiles);x+=Quality)
        {
            for (u32 z=TileZ;z<(TileZ+SizeOfTiles);z+=Quality)
            {
                if (NbsVertices < (SOTiles*SOTiles)-SOTiles-1)
                {
                    Index = NbsVertices;
                    u32 TestValue = ( (((x-TileX)/Quality)+1) * ((z-TileZ)/Quality) + ((x-TileX)/Quality) );
                    if (Index != TestValue || (x-TileX==0 && z < TileZ+SizeOfTiles-Quality))
                    {
                        CTTileBuffer[i]->Indices[NbsIndices++]=Index;
                        CTTileBuffer[i]->Indices[NbsIndices++]=Index+1;
                        CTTileBuffer[i]->Indices[NbsIndices++]=Index+SOTiles+1;
                        CTTileBuffer[i]->Indices[NbsIndices++]=Index;
                        CTTileBuffer[i]->Indices[NbsIndices++]=Index+SOTiles+1;
                        CTTileBuffer[i]->Indices[NbsIndices++]=Index+SOTiles;
                    }
                }

                video::S3DVertex2TCoords Vertex;
                Vertex.Normal = core::vector3df(0,1,0);
                Vertex.Pos.X = (f32)x;
                video::SColor pixelColor(Heightmap->getPixel(x,z));
                Vertex.Pos.Y = (f32) pixelColor.getLuminance()/10.0f;
                Vertex.Pos.Z = (f32)z;
                Vertex.TCoords = core::vector2d<f32>( (f32)(x*tdSize), (f32)(z*tdSize));
                Vertex.TCoords2 = core::vector2d<f32>( (f32)(x*tdSize), (f32)(z*tdSize))*ScaleTexture;

                CTTileBuffer[i]->Vertices[NbsVertices]=Vertex;

                NbsVertices++;
            }
        }

        CTTileBuffer[i]->Material.Lighting = true;
        //CTTileBuffer[i]->Material.Wireframe = true;
        CTTileBuffer[i]->Material.BackfaceCulling = true;
        CTTileBuffer[i]->Material.GouraudShading=true;
        CTTileBuffer[i]->Material.FogEnable=false;

        CTTileBuffer[i]->Material.DiffuseColor=video::SColor(255,255,255,255);
        CTTileBuffer[i]->Material.AmbientColor=video::SColor(255,255,255,255);
        CTTileBuffer[i]->Material.EmissiveColor=video::SColor(255,255,255,255);

        CTTileBuffer[i]->Vertices.set_used(NbsVertices);
        CTTileBuffer[i]->Indices.set_used(NbsIndices);

        for(s32 j = 0; j < ((Quality+1)/2); j++)
        {
            for(u32 index = 2; index < (SOTiles * SOTiles - 2); index++)
            {
                //A[i] = (1/8)*(A[i-2] + 2*A[i-1] + 2*A[i] + 2*A[i+1] + A[i+2]);
                CTTileBuffer[i]->Vertices[index].Pos.Y += (1/8)*
                (CTTileBuffer[i]->Vertices[index-2].Pos.Y +
                2*CTTileBuffer[i]->Vertices[index-1].Pos.Y +
                2*CTTileBuffer[i]->Vertices[index].Pos.Y +
                2*CTTileBuffer[i]->Vertices[index+1].Pos.Y +
                CTTileBuffer[i]->Vertices[index+2].Pos.Y);
            }
        }

        for(s32 k = 0; k < ((Quality+1)/2); k++)
        {
            for(u32 index = SOTiles; index < (SOTiles * (SOTiles - 1)); index++)
            {
                CTTileBuffer[i]->Vertices[index].Pos.Y = (CTTileBuffer[i]->Vertices[index - SOTiles].Pos.Y + CTTileBuffer[i]->Vertices[index + SOTiles].Pos.Y ) / 2.0f;
            }
        }

        //Calculate the normals
        calculateNormals(CTTileBuffer[i],SOTiles);

        //Recalculate the bounding box
        CTTileBuffer[i]->recalculateBoundingBox();

        //Add the buffer to the Terrain Mesh
        TerrainMesh->addMeshBuffer(CTTileBuffer[i]);

        TileX+=SizeOfTiles-1;
        if(TileX >= Size)
        {
            TileX=0;

            TileZ+=SizeOfTiles-1;
            if(TileZ >= Size)
            {
                TileZ=0;
            }
        }
    }
    AutomaticCullingState = scene::EAC_OFF;
    Heightmap->drop();
}

CTerrain::~CTerrain()
{
    for(u32 i=0;i<NbsTiles;++i)
    {
        if (CTerrain::CTTileBuffer[i] != NULL)
        {
            CTerrain::CTTileBuffer[i]->drop();
        }
    }

    delete [] CTerrain::CTTileBuffer;

    if(CTerrain::TerrainMesh != NULL)
    {
        CTerrain::TerrainMesh->drop();
    }
}

void CTerrain::OnRegisterSceneNode()
{
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}

void CTerrain::render()
{
    scene::ICameraSceneNode* cam = SceneManager->getActiveCamera();
    const scene::SViewFrustum* frustum = cam->getViewFrustum();
    video::IVideoDriver* Driver = SceneManager->getVideoDriver();
    core::vector3df Pos = cam->getPosition();
    cam->updateAbsolutePosition();

    Pos.Y=0.0f;

    for (u32 i=0;i<NbsTiles;i++)
    {
        if (CTTileBuffer[i] != NULL)
        {
            Driver->setTransform(video::ETS_WORLD,AbsoluteTransformation);

            //DEBUG HERE
            if(Debug==true)
            {
                video::SMaterial Mat;
                Mat.AmbientColor = video::SColor(255,255,255,255);
                Mat.DiffuseColor = video::SColor(255,255,255,255);
                Mat.EmissiveColor = video::SColor(255,0,255,0);
                Driver->setMaterial(Mat);
                Driver->draw3DBox(CTTileBuffer[i]->getBoundingBox(),video::SColor(255,255,255,255));
            }

            if( frustum->getBoundingBox().intersectsWithBox(CTTileBuffer[i]->getBoundingBox())==true)
            {
                f64 ActualDistance = CTTileBuffer[i]->BoundingBox.getCenter().getDistanceFrom(Pos);
                if(ActualDistance < RenderDistance)
                {
                    Driver->setMaterial(video::SMaterial(CTTileBuffer[i]->Material));
                    Driver->drawIndexedTriangleList(&CTTileBuffer[i]->Vertices[0],CTTileBuffer[i]->getVertexCount(),&CTTileBuffer[i]->Indices[0], CTTileBuffer[i]->getIndexCount()/3 );
                    //Driver->drawMeshBuffer(CTTileBuffer[i]);
                }
            }
        }
    }
}

void CTerrain::setPosition(const core::vector3df &Pos)
{
    for (u32 i=0;i<NbsTiles;i++)
    {
        if (CTTileBuffer[i] != NULL)
        {
            for (u32 j=0;j<CTTileBuffer[i]->getVertexCount();++j)
            {
                CTTileBuffer[i]->Vertices[j].Pos+=Pos;
            }
            CTTileBuffer[i]->recalculateBoundingBox();
        }
    }
}

void CTerrain::setScale(const core::vector3df &Scale)
{
    for (u32 i=0;i<NbsTiles;i++)
    {
        if (CTTileBuffer[i] != NULL)
        {
            for (u32 j=0;j<CTTileBuffer[i]->getVertexCount();++j)
            {
                CTTileBuffer[i]->Vertices[j].Pos*=Scale;
            }
            CTTileBuffer[i]->recalculateBoundingBox();
        }
    }
}

const core::aabbox3d<f32>& CTerrain::getBoundingBox() const
{
    return Box;
}

u32 CTerrain::getMaterialCount()
{
    return 1;
}

video::SMaterial& CTerrain::getMaterial(u32 i)
{
    return Material;
}

void CTerrain::ActivateSplattingTextures(scene::ISceneManager* smgr,f32 Height,f32 Fog,video::SColorf FogColor)
{
    video::IVideoDriver* driver = smgr->getVideoDriver();
    s32 newMaterialType1 = 0;
    video::IGPUProgrammingServices* gpu = smgr->getVideoDriver()->getGPUProgrammingServices();

    if (driver->getDriverType() != video::EDT_OPENGL)
    {
        //Merci à DeusXL pour son shader :D
        c8 ShaderFileName[] =
            "float4x4 mWorldViewProj;\n" \
            "float4x4 mWorld;\n" \
            "float3 cameraPos;\n" \
            "float TerrainHeight;\n" \
            "float FogDistance;\n" \

            "struct VS_OUTPUT\n" \
            "{\n" \
            "float4 Position : POSITION;\n" \
            "float4 Diffuse : COLOR0;\n" \
            "float2 TexCoord1 : TEXCOORD1;\n" \
            "};\n" \

            "VS_OUTPUT vertexMain( in float4 vPosition : POSITION,in float3 vNormal : NORMAL,float2 texCoord1 : TEXCOORD1)\n" \
            "{\n" \
            "VS_OUTPUT Output;\n" \
            "Output.Position = mul(vPosition, mWorldViewProj);\n" \
            "float4 position = mul(vPosition, mWorld);\n" \
            "float dist = sqrt ( pow(position.x - cameraPos.x, 2.0f) +\n" \
            "pow(position.y - cameraPos.y, 2.0f) +\n" \
            "pow(position.z - cameraPos.z, 2.0f));\n" \
            "Output.Diffuse = float4(vPosition.y / TerrainHeight, dist / FogDistance, 0.0f, 0.0f);\n" \
            "Output.TexCoord1 = texCoord1;\n" \
            "return Output;\n" \
            "}\n" \

            "struct PS_OUTPUT\n" \
            "{\n" \
            "float4 RGBColor : COLOR0;\n" \
            "};\n" \

            "sampler2D tex[4];\n" \
            "float4 fog;\n" \
            "PS_OUTPUT pixelMain( float2 TexCoord1 : TEXCOORD1,float4 Position : POSITION,float4 Diffuse : COLOR0 )\n" \
            "{\n" \
            "PS_OUTPUT Output;\n" \
            "float heightpercent = Diffuse.x;\n" \
            "float dist = Diffuse.y;\n" \

            "float4 grasscolor = tex2D(tex[0], TexCoord1 * 5.0f) * pow((1.0f - heightpercent), 4.0f);\n" \
            "float4 rockcolor = tex2D(tex[1], TexCoord1 * 5.0f) * pow((1.0f - abs(0.5f - heightpercent)), 4.0f);\n" \
            "float4 snowcolor = tex2D(tex[2], TexCoord1 * 5.0f) * pow(heightpercent,4.0f);\n" \
            "float4 detailcolor = tex2D(tex[3], TexCoord1 * 5.0f) * pow((1.0f - abs(0.7f - heightpercent)), 4.0f);\n" \
            "Output.RGBColor = (grasscolor + rockcolor + snowcolor  + detailcolor);\n" \

            "if (dist >= 0.5f)\n" \
            "{\n" \
            "Output.RGBColor *= (1.0f - (dist-0.5f));\n" \
            "Output.RGBColor += (fog  * (dist-0.5f));\n" \
            "}\n" \

            "return Output;\n" \
            "}\n";

        if (gpu)
        {
            MyShaderCallBack* mc = new MyShaderCallBack();
            mc->setSplatScene(smgr,Height,Fog,FogColor);
            newMaterialType1 = gpu->addHighLevelShaderMaterial(
                ShaderFileName, "vertexMain", video::EVST_VS_2_0,
                ShaderFileName, "pixelMain", video::EPST_PS_2_0,
                mc, video::EMT_SOLID,0);
            mc->drop();
        }
    }
    else
    {
        c8 ShaderFragment[] =
            "//\n" \
            "// Structure definitions\n" \
            "//\n" \
            "struct VS_OUTPUT {\n" \
            "vec4 Position;\n" \
            "vec4 Diffuse;\n" \
            "vec2 TexCoord1;\n" \
            "};\n" \

            "struct PS_OUTPUT {\n" \
            "vec4 RGBColor;\n" \
            "};\n" \


            "//\n" \
            "// Global variable definitions\n" \
            "//\n" \

            "uniform vec4 fog;\n" \
            "uniform sampler2D texgrass,texrock,texsnow,texdetail;\n" \

            "//\n" \
            "// Function declarations\n" \
            "//\n" \
            "PS_OUTPUT pixelMain( in vec2 TexCoord1, in vec4 Position, in vec4 Diffuse );\n" \
            "//\n" \
            "// Function definitions\n" \
            "//\n" \
            "PS_OUTPUT pixelMain( in vec2 TexCoord1, in vec4 Position, in vec4 Diffuse ) {\n" \
            "float heightpercent;\n" \
            "float dist;\n" \
            "vec4 grasscolor;\n" \
            "vec4 rockcolor;\n" \
            "vec4 snowcolor;\n" \
            "vec4 detailcolor;\n" \
            "PS_OUTPUT Output;\n" \

            "heightpercent = Diffuse.x ;\n" \
            "dist = Diffuse.y ;\n" \
            "grasscolor = (texture2D( texgrass, (TexCoord1 * 5.00000)) * pow( (1.00000 - heightpercent), 4.00000));\n" \
            "rockcolor = (texture2D( texrock, (TexCoord1 * 5.00000)) * pow( (1.00000 - abs( (0.500000 - heightpercent) )), 4.00000));\n" \
            "snowcolor = (texture2D( texsnow, (TexCoord1 * 5.00000)) * pow( heightpercent, 4.00000));\n" \
            "detailcolor = (texture2D( texdetail, (TexCoord1 * 5.00000)) * pow( (1.00000 - abs( (0.700000 - heightpercent) )), 4.00000));\n" \
            "Output.RGBColor = (((grasscolor + rockcolor) + snowcolor) + detailcolor);\n" \
            "if ( (dist >= 0.500000) ){\n" \
            "Output.RGBColor *= (1.00000 - (dist - 0.500000));\n" \
            "Output.RGBColor += (fog * (dist - 0.500000));\n" \
            "}\n" \
            "return Output;\n" \
            "}\n" \

            "//\n" \
            "// Translator's entry point\n" \
            "//\n" \
            "void main() {\n" \
            "PS_OUTPUT xlat_retVal;\n" \
            "xlat_retVal = pixelMain( vec2(gl_TexCoord[1]), vec4(gl_FragCoord), vec4(gl_Color));\n" \
            "gl_FragData[0] = vec4( xlat_retVal.RGBColor);\n" \
            "}\n";

        c8 ShaderVertex[]=
            "//\n" \
            "// Structure definitions\n" \
            "//\n" \

            "struct VS_OUTPUT {\n" \
            "vec4 Position;\n" \
            "vec4 Diffuse;\n" \
            "vec2 TexCoord1;\n" \
            "};\n" \

            "struct PS_OUTPUT {\n" \
            "vec4 RGBColor;\n" \
            "};\n" \

            "//\n" \
            "// Global variable definitions\n" \
            "//\n" \

            "uniform float FogDistance;\n" \
            "uniform float TerrainHeight;\n" \
            "uniform vec3 cameraPos;\n" \
            "uniform mat4 mWorld;\n" \
            "uniform mat4 mWorldViewProj;\n" \

            "//\n" \
            "// Function declarations\n" \
            "//\n" \

            "VS_OUTPUT vertexMain( in vec4 vPosition, in vec3 vNormal, in vec2 texCoord1 );\n" \

            "//\n" \
            "// Function definitions\n" \
            "//\n" \

            "VS_OUTPUT vertexMain( in vec4 vPosition, in vec3 vNormal, in vec2 texCoord1 ) {\n" \
            "VS_OUTPUT Output;\n" \
            "vec4 position;\n" \
            "float dist;\n" \

            "Output.Position = ( vPosition * mWorldViewProj );\n" \
            "position = ( vPosition * mWorld );\n" \
            "dist = sqrt( ((pow( (position.x  - cameraPos.x ), 2.00000) + pow( (position.y  - cameraPos.y ), 2.00000)) + pow( (position.z  - cameraPos.z ), 2.00000)) );\n" \
            "Output.Diffuse = vec4( (vPosition.y  / TerrainHeight), (dist / FogDistance), 0.000000, 0.000000);\n" \
            "Output.TexCoord1 = texCoord1;\n" \
            "return Output;\n" \
            "}\n" \


            "//\n" \
            "// Translator's entry point\n" \
            "//\n" \
            "void main() {\n" \
            "VS_OUTPUT xlat_retVal;\n" \

            "xlat_retVal = vertexMain( vec4(gl_Vertex), vec3(gl_Normal), vec2(gl_MultiTexCoord1));\n" \

            "gl_Position = vec4( xlat_retVal.Position);\n" \
            "gl_FrontColor = vec4( xlat_retVal.Diffuse);\n" \
            "gl_TexCoord[1] = vec4( xlat_retVal.TexCoord1, 0.0, 0.0);\n" \
            "}\n";

        if (gpu)
        {
            MyShaderCallBack* mc = new MyShaderCallBack();
            mc->setSplatScene(smgr,Height,Fog,FogColor);
            newMaterialType1 = gpu->addHighLevelShaderMaterial(
                ShaderVertex, "main", video::EVST_VS_1_1,
                ShaderFragment, "main", video::EPST_PS_1_1,
                mc, video::EMT_SOLID,0);
            mc->drop();
        }
    }
    setMaterialType((video::E_MATERIAL_TYPE)newMaterialType1);
}

void CTerrain::setColorTexture(c8* FileName)
{
    for (u32 i=0;i<NbsTiles;++i)
    {
        if (CTTileBuffer[i] != NULL)
        {
            CTTileBuffer[i]->Material.MaterialType = video::EMT_SOLID;
            CTTileBuffer[i]->Material.Textures[0] = SceneManager->getVideoDriver()->getTexture(FileName);
        }
    }
}

void CTerrain::setDetailTexture(c8* FileName)
{
    for (u32 i=0;i<NbsTiles;++i)
    {
        if (CTTileBuffer[i] != NULL)
        {
            CTTileBuffer[i]->Material.MaterialType = video::EMT_DETAIL_MAP;
            CTTileBuffer[i]->Material.Textures[1] = SceneManager->getVideoDriver()->getTexture(FileName);
        }
    }
}

void CTerrain::SetTextureSplat(u32 NumTex,c8* FileName)
{
        for (u32 i=0;i<NbsTiles;++i)
    {
        if (CTTileBuffer[i] != NULL)
        {
            CTTileBuffer[i]->Material.Textures[NumTex] = SceneManager->getVideoDriver()->getTexture(FileName);
        }
    }
}

void CTerrain::setDebugMode(bool Enable)
{
    Debug=Enable;
}

void CTerrain::setRenderDistance(f32 Distance)
{
    RenderDistance = Distance;
}

void CTerrain::setMaterialType(video::E_MATERIAL_TYPE Mat)
{
    for (u32 i=0;i < NbsTiles;++i)
    {
        if (CTTileBuffer[i] != NULL)
        {
            CTTileBuffer[i]->Material.MaterialType = Mat;
        }
    }
}

scene::IMesh* CTerrain::getMesh()
{
    return (scene::IMesh*)TerrainMesh;
}

f32 CTerrain::getHeight(f32 x,f32 z)
{
    scene::SMeshBufferLightMap* TempBuffer=NULL;

    f32 ValueReturn = 0.0f;

    for (u32 i=0;i < NbsTiles;++i)
    {
        if (CTTileBuffer[i] != NULL)
        {
            core::vector3df Vec(x,CTTileBuffer[i]->getBoundingBox().getCenter().Y,z);
            if(CTTileBuffer[i]->getBoundingBox().isPointInside(Vec))
            {
                TempBuffer=CTTileBuffer[i];
                break;
            }
        }
    }

    if(TempBuffer != NULL)
    {
        //Si le TempBuffer renvoi différent de null, on se situ dans un tile
        scene::SMesh* Mesh=new scene::SMesh();
        Mesh->addMeshBuffer(TempBuffer);
        scene::ITriangleSelector* selector= SceneManager->createTriangleSelector((scene::IMesh*)Mesh,this);
        this->setTriangleSelector(selector);

        core::line3d<f32> line;
        line.start = core::vector3d<f32>(x,-200000,z);
        line.end = core::vector3d<f32>(x,200000,z);

        core::vector3df intersection;
        core::triangle3df tri;

        if (SceneManager->getSceneCollisionManager()->getCollisionPoint(line, selector, intersection,tri))
        {
            ValueReturn = intersection.Y;
        }
        selector->drop();
        Mesh->drop();
    }
    else
    {
        ValueReturn=-999999.999f;
    }

    return ValueReturn;
}

//Take from the irrlicht source code
void CTerrain::calculateNormals ( scene::SMeshBufferLightMap* pMeshBuffer,s32 Size)
{
    s32 count;
    //s32 Size = 4;
    core::vector3df a, b, c, t;

    for (s32 x=0; x<Size; ++x)
        for (s32 z=0; z<Size; ++z)
        {
            count = 0;
            core::vector3df normal;

            // top left
            if (x>0 && z>0)
            {
                a = pMeshBuffer->Vertices[(x-1)*Size+z-1].Pos;
                b = pMeshBuffer->Vertices[(x-1)*Size+z].Pos;
                c = pMeshBuffer->Vertices[x*Size+z].Pos;
                b -= a;
                c -= a;
                t = b.crossProduct ( c );
                t.normalize ( );
                normal += t;

                a = pMeshBuffer->Vertices[(x-1)*Size+z-1].Pos;
                b = pMeshBuffer->Vertices[x*Size+z-1].Pos;
                c = pMeshBuffer->Vertices[x*Size+z].Pos;
                b -= a;
                c -= a;
                t = b.crossProduct ( c );
                t.normalize ( );
                normal += t;

                count += 2;
            }

            // top right
            if (x>0 && z<Size-1)
            {
                a = pMeshBuffer->Vertices[(x-1)*Size+z].Pos;
                b = pMeshBuffer->Vertices[(x-1)*Size+z+1].Pos;
                c = pMeshBuffer->Vertices[x*Size+z+1].Pos;
                b -= a;
                c -= a;
                t = b.crossProduct ( c );
                t.normalize ( );
                normal += t;

                a = pMeshBuffer->Vertices[(x-1)*Size+z].Pos;
                b = pMeshBuffer->Vertices[x*Size+z+1].Pos;
                c = pMeshBuffer->Vertices[x*Size+z].Pos;
                b -= a;
                c -= a;
                t = b.crossProduct ( c );
                t.normalize ( );
                normal += t;

                count += 2;
            }

            // bottom right
            if (x<Size-1 && z<Size-1)
            {
                a = pMeshBuffer->Vertices[x*Size+z+1].Pos;
                b = pMeshBuffer->Vertices[x*Size+z+1].Pos;
                c = pMeshBuffer->Vertices[(x+1)*Size+z+1].Pos;
                b -= a;
                c -= a;
                t = b.crossProduct ( c );
                t.normalize ( );
                normal += t;

                a = pMeshBuffer->Vertices[x*Size+z+1].Pos;
                b = pMeshBuffer->Vertices[(x+1)*Size+z+1].Pos;
                c = pMeshBuffer->Vertices[(x+1)*Size+z].Pos;
                b -= a;
                c -= a;
                t = b.crossProduct ( c );
                t.normalize ( );
                normal += t;

                count += 2;
            }

            // bottom left
            if (x<Size-1 && z>0)
            {
                a = pMeshBuffer->Vertices[x*Size+z-1].Pos;
                b = pMeshBuffer->Vertices[x*Size+z].Pos;
                c = pMeshBuffer->Vertices[(x+1)*Size+z].Pos;
                b -= a;
                c -= a;
                t = b.crossProduct ( c );
                t.normalize ( );
                normal += t;

                a = pMeshBuffer->Vertices[x*Size+z-1].Pos;
                b = pMeshBuffer->Vertices[(x+1)*Size+z].Pos;
                c = pMeshBuffer->Vertices[(x+1)*Size+z-1].Pos;
                b -= a;
                c -= a;
                t = b.crossProduct ( c );
                t.normalize ( );
                normal += t;

                count += 2;
            }

            if ( count != 0 )
            {
                normal.normalize ( );
            }
            else
            {
                normal.set( 0.0f, 1.0f, 0.0f );
            }

            pMeshBuffer->Vertices[x * Size + z].Normal = normal;
        }
}
