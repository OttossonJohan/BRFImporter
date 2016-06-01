#include "Fetch.h"
#include "FileData.h"
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
using namespace BRFImporterLib;

//returns the mainheader info
MainHeader*  BRFImporterLib::Fetch::Main()
{
	return this->FetchDataContainer->getMain();
}
//returns a whole mesh from an array using its ID
MeshData* Fetch::Mesh(unsigned int meshID)
{
	if (meshID > this->FetchDataContainer->getMain()->meshAmount)
	{
		return nullptr;
	}
	else
	{
		for (unsigned int i = 0; i < (this->FetchDataContainer->getMain()->meshAmount); i++)
		{
			if (meshID == this->FetchDataContainer->GetMeshHeader(i)->objectID)
			{
				return this->FetchDataContainer->GetMesh(i);
			}
		}
		return nullptr;
	}
}
//returns a material from tech using the materials ID.
MaterialContainer* Fetch::Material(unsigned int materialID)
{
	if (materialID > this->FetchDataContainer->getMain()->materialAmount)
	{
		return nullptr;
	}
	else
	{
		for (unsigned int i = 0; i < (this->FetchDataContainer->getMain()->materialAmount); i++)
		{
			if (materialID == this->FetchDataContainer->GetMaterial(i)->Id)
			{
				return this->FetchDataContainer->GetMaterial(i);
			}
		}
		return nullptr;
	}
}

SkeletonData* Fetch::Skeleton(unsigned int skeletonID)
{
	if (skeletonID > this->FetchDataContainer->getMain()->skeletonAmount)
	{
		return nullptr;
	}
	else
	{
		for (unsigned int i = 0; i < (this->FetchDataContainer->getMain()->skeletonAmount); i++)
		{
			if (skeletonID == this->FetchDataContainer->GetSkeleton(i)->GetSkeletonData()->skeletonID)
			{
				return this->FetchDataContainer->GetSkeleton(i);
			}
		}
		return nullptr;
	}
}
AnimationHeader* Fetch::Animation(unsigned int skeletonID, unsigned int animationID)
{
	if (skeletonID > this->FetchDataContainer->getMain()->skeletonAmount)
	{
		return nullptr;
	}
	else
	{
		for (unsigned int i = 0; i < (this->FetchDataContainer->getMain()->skeletonAmount); i++)
		{
			if (skeletonID == this->FetchDataContainer->GetSkeleton(i)->GetSkeletonData()->skeletonID)
			{
				for (unsigned int j = 0; j < (this->FetchDataContainer->GetSkeleton(i)->GetSkeletonData()->animationCount); j++)
				{
					if (animationID == (this->FetchDataContainer->GetSkeleton(i)->GetAnimationID(j)))
					{
						return this->FetchDataContainer->GetSkeleton(i)->GetAnimation(j);
					}
				}
			}
		}
		return nullptr;
	}
}

LightData * BRFImporterLib::Fetch::Light(unsigned int lightType, unsigned int lightID)
{
	if (lightType == 0)
	{
		return this->FetchDataContainer->getLight(lightType, lightID);
	}
	else if (lightType == 1)
	{
		return this->FetchDataContainer->getLight(lightType, lightID);
	}
	else if (lightType == 2)
	{
		return this->FetchDataContainer->getLight(lightType, lightID);
	}
	else if (lightType == 3)
	{
		return this->FetchDataContainer->getLight(lightType, lightID);
	}
	else
	{
		return nullptr;
	}
}

MorphData * BRFImporterLib::Fetch::MorphAnimation(unsigned int morphAnimationID)
{
	if (morphAnimationID > this->FetchDataContainer->getMain()->morphAnimAmount)
	{
		return nullptr;
	}
	else
	{
			return this->FetchDataContainer->GetMorphAnimation(morphAnimationID);
	}
}

//CON DECON
Fetch::Fetch(std::shared_ptr<FetchContainer> SrcFetchData)
{
	this->FetchDataContainer = SrcFetchData;
}
Fetch::Fetch()
{

}
Fetch::~Fetch()
{

}

//fetchcontainerstuff
MainHeader* FetchContainer::getMain()
{
	return this->mainData.get();
}
MeshHeader* FetchContainer::GetMeshHeader(unsigned int meshID)
{
	return this->meshes[meshID]->GetMeshData();
}
MeshData* FetchContainer::GetMesh(unsigned int meshID)
{
	return this->meshes[meshID].get();
}
MaterialContainer* FetchContainer::GetMaterial(unsigned int materialID)
{
	return this->materialData->GetMaterialData(materialID);
}
SkeletonData* FetchContainer::GetSkeleton(unsigned int skeletonID)
{
	return this->skeletons[skeletonID].get();
}
LightData * BRFImporterLib::FetchContainer::getLight(unsigned int lightType, unsigned int lightID)
{
	if (lightType == 0)
	{
		if (lightID > this->lights->GetLightData()->spotCount)
		{
			return this->lights->GetSpotLightData[lightID].get();
		}
	}
	else if (lightType == 1)
	{
		if (lightID > this->lights->GetLightData()->areaCount)
		{
			return this->lights->GetAreaLightData[lightID].get();
		}
	}
	else if (lightType == 2)
	{
		if (lightID > this->lights->GetLightData()->pointCount)
		{
			return this->lights->GetPointLightData[lightID].get();
		}
	}
	else if (lightType == 3)
	{
		if (lightID > this->lights->GetLightData()->directionalCount)
		{
			return this->lights->GetDirLightData[lightID].get();
		}
	}
	else
	{
		return nullptr;
	}
}
MorphData * BRFImporterLib::FetchContainer::GetMorphAnimation(unsigned int morphAnimationID)
{
	return this->morphAnimations[morphAnimationID].get();
}
FetchContainer::FetchContainer(std::shared_ptr<MainHeader> tempMain, std::vector<std::shared_ptr<MeshData>> meshVector, std::shared_ptr<MaterialData> materialData, std::vector<std::shared_ptr<SkeletonData>> skeletonVector,std::shared_ptr<LightData> tempLightData, std::vector<std::shared_ptr<MorphData>> morphVector)
{
	this->mainData = tempMain;
	this->meshes = meshVector;
	this->materialData = materialData;
	this->skeletons = skeletonVector;
	this->lights = tempLightData;
	this->morphAnimations = morphVector;
}
FetchContainer::~FetchContainer()
{

}
