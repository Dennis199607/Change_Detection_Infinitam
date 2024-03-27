// Copyright 2014-2017 Oxford University Innovation Limited and the authors of InfiniTAM

#pragma once

#include "../Interface/ITMVisualisationEngine.h"

struct RenderingBlock;

namespace ITMLib
{
	template<class TVoxel, class TIndex>
	class ITMVisualisationEngine_CUDA : public ITMVisualisationEngine < TVoxel, TIndex >
	{
	private:
		uint *noTotalPoints_device;

		int sizeX, sizeY;
		float minX, minY, minZ, maxX, maxY, maxZ;
		float* change_from;
		float* change_to;
		int* change_voxelTypes;

	public:
		explicit ITMVisualisationEngine_CUDA(void);
		~ITMVisualisationEngine_CUDA(void);

		ITMRenderState* CreateRenderState(const ITMScene<TVoxel, TIndex> *scene, const Vector2i & imgSize) const;
		void FindVisibleBlocks(const ITMScene<TVoxel,TIndex> *scene, const ORUtils::SE3Pose *pose, const ITMIntrinsics *intrinsics, ITMRenderState *renderState) const;
		int CountVisibleBlocks(const ITMScene<TVoxel,TIndex> *scene, const ITMRenderState *renderState, int minBlockId, int maxBlockId) const;
		void CreateExpectedDepths(const ITMScene<TVoxel,TIndex> *scene, const ORUtils::SE3Pose *pose, const ITMIntrinsics *intrinsics, ITMRenderState *renderState) const;
		void RenderImage(const ITMScene<TVoxel,TIndex> *scene, const ORUtils::SE3Pose *pose, const ITMIntrinsics *intrinsics, const ITMRenderState *renderState,
			ITMUChar4Image *outputImage, IITMVisualisationEngine::RenderImageType type = IITMVisualisationEngine::RENDER_SHADED_GREYSCALE,
			IITMVisualisationEngine::RenderRaycastSelection raycastType = IITMVisualisationEngine::RENDER_FROM_NEW_RAYCAST) const;
		void RenderChanges(const ITMScene<TVoxel, ITMVoxelBlockHash>* scene, const ORUtils::SE3Pose* pose, const ITMIntrinsics* intrinsics,
			const ITMRenderState* renderState, ITMUChar4Image* outputImage,
			float* change_from, float* change_to, int* change_voxelTypes, int minX, int minY, int minZ, int maxX, int maxY, int maxZ,
			RenderImageType type = IITMVisualisationEngine::RENDER_SHADED_GREYSCALE, RenderRaycastSelection raycastType = IITMVisualisationEngine::RENDER_FROM_NEW_RAYCAST) const;
		void FindSurface(const ITMScene<TVoxel,TIndex> *scene, const ORUtils::SE3Pose *pose, const ITMIntrinsics *intrinsics, const ITMRenderState *renderState) const;
		void CreatePointCloud(const ITMScene<TVoxel,TIndex> *scene, const ITMView *view, ITMTrackingState *trackingState, ITMRenderState *renderState, bool skipPoints) const;
		void CreateICPMaps(const ITMScene<TVoxel,TIndex> *scene, const ITMView *view, ITMTrackingState *trackingState, ITMRenderState *renderState) const;
		void ForwardRender(const ITMScene<TVoxel,TIndex> *scene, const ITMView *view, ITMTrackingState *trackingState, ITMRenderState *renderState) const;
		void updateDepthIntervals(ITMScene<TVoxel, ITMVoxelBlockHash>* activeScene, ITMScene<TVoxel, ITMVoxelBlockHash>* oldScene, const ORUtils::SE3Pose* pose, const ITMIntrinsics* intrinsics,
			const ITMRenderState* renderState, ITMUChar4Image* outputImage, RenderImageType type = IITMVisualisationEngine::RENDER_SHADED_GREYSCALE, RenderRaycastSelection raycastType = IITMVisualisationEngine::RENDER_FROM_NEW_RAYCAST);
	};

	template<class TVoxel>
	class ITMVisualisationEngine_CUDA<TVoxel, ITMVoxelBlockHash> : public ITMVisualisationEngine < TVoxel, ITMVoxelBlockHash >
	{
	private:
		uint *noTotalPoints_device;
		RenderingBlock *renderingBlockList_device;
		uint *noTotalBlocks_device;
		int *noVisibleEntries_device;

		int sizeX, sizeY;
		float minX, minY, minZ, maxX, maxY, maxZ;
		float* change_from;
		float* change_to;
		int* change_voxelTypes;
	public:
		explicit ITMVisualisationEngine_CUDA(void);
		~ITMVisualisationEngine_CUDA(void);

		ITMRenderState_VH* CreateRenderState(const ITMScene<TVoxel, ITMVoxelBlockHash> *scene, const Vector2i & imgSize) const;
		void FindVisibleBlocks(const ITMScene<TVoxel,ITMVoxelBlockHash> *scene, const ORUtils::SE3Pose *pose, const ITMIntrinsics *intrinsics, ITMRenderState *renderState) const;
		int CountVisibleBlocks(const ITMScene<TVoxel,ITMVoxelBlockHash> *scene, const ITMRenderState *renderState, int minBlockId, int maxBlockId) const;
		void CreateExpectedDepths(const ITMScene<TVoxel,ITMVoxelBlockHash> *scene, const ORUtils::SE3Pose *pose, const ITMIntrinsics *intrinsics, ITMRenderState *renderState) const;
		void RenderImage(const ITMScene<TVoxel,ITMVoxelBlockHash> *scene, const ORUtils::SE3Pose *pose, const ITMIntrinsics *intrinsics, const ITMRenderState *renderState,
			ITMUChar4Image *outputImage, IITMVisualisationEngine::RenderImageType type = IITMVisualisationEngine::RENDER_SHADED_GREYSCALE,
			IITMVisualisationEngine::RenderRaycastSelection raycastType = IITMVisualisationEngine::RENDER_FROM_NEW_RAYCAST) const;
		void RenderChanges(const ITMScene<TVoxel, ITMVoxelBlockHash>* scene, const ORUtils::SE3Pose* pose, const ITMIntrinsics* intrinsics,
			const ITMRenderState* renderState, ITMUChar4Image* outputImage,
			float* change_from, float* change_to, int* change_voxelTypes, int minX, int minY, int minZ, int maxX, int maxY, int maxZ,
			RenderImageType type = RENDER_SHADED_GREYSCALE, RenderRaycastSelection raycastType = RENDER_FROM_NEW_RAYCAST) const;
		void FindSurface(const ITMScene<TVoxel,ITMVoxelBlockHash> *scene, const ORUtils::SE3Pose *pose, const ITMIntrinsics *intrinsics, const ITMRenderState *renderState) const;
		void CreatePointCloud(const ITMScene<TVoxel,ITMVoxelBlockHash> *scene, const ITMView *view, ITMTrackingState *trackingState, ITMRenderState *renderState, bool skipPoints) const;
		void CreateICPMaps(const ITMScene<TVoxel,ITMVoxelBlockHash> *scene, const ITMView *view, ITMTrackingState *trackingState, ITMRenderState *renderState) const;
		void ForwardRender(const ITMScene<TVoxel,ITMVoxelBlockHash> *scene, const ITMView *view, ITMTrackingState *trackingState, ITMRenderState *renderState) const;
		void updateDepthIntervals(ITMScene<TVoxel, ITMVoxelBlockHash>* activeScene, ITMScene<TVoxel, ITMVoxelBlockHash>* oldScene, const ORUtils::SE3Pose* pose, const ITMIntrinsics* intrinsics,
			const ITMRenderState* renderState, ITMUChar4Image* outputImage, RenderImageType type = IITMVisualisationEngine::RENDER_SHADED_GREYSCALE, RenderRaycastSelection raycastType = IITMVisualisationEngine::RENDER_FROM_NEW_RAYCAST);
	};
}
