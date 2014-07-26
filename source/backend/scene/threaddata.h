//******************************************************************************
///
/// @file backend/scene/threaddata.h
///
/// @todo   What's in here?
///
/// @copyright
/// @parblock
///
/// UberPOV Raytracer version 1.37.
/// Portions Copyright 2013-2014 Christoph Lipka.
///
/// UberPOV 1.37 is an experimental unofficial branch of POV-Ray 3.7, and is
/// subject to the same licensing terms and conditions.
///
/// ----------------------------------------------------------------------------
///
/// Persistence of Vision Ray Tracer ('POV-Ray') version 3.7.
/// Copyright 1991-2014 Persistence of Vision Raytracer Pty. Ltd.
///
/// POV-Ray is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Affero General Public License as
/// published by the Free Software Foundation, either version 3 of the
/// License, or (at your option) any later version.
///
/// POV-Ray is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU Affero General Public License for more details.
///
/// You should have received a copy of the GNU Affero General Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.
///
/// ----------------------------------------------------------------------------
///
/// POV-Ray is based on the popular DKB raytracer version 2.12.
/// DKBTrace was originally written by David K. Buck.
/// DKBTrace Ver 2.0-2.12 were written by David K. Buck & Aaron A. Collins.
///
/// @endparblock
///
//******************************************************************************

#ifndef POVRAY_BACKEND_THREADDATA_H
#define POVRAY_BACKEND_THREADDATA_H

#include <vector>
#include <stack>

#include "base/types.h"
#include "backend/frame.h"
#include "backend/pattern/pattern.h"
#include "backend/shape/mesh.h"
#include "backend/support/randomsequences.h"
#include "backend/support/statistics.h"
#include "backend/support/task.h"

namespace pov
{

using namespace pov_base;

class SceneData;
class ViewData;
class FunctionVM;
struct FPUContext;
struct ISO_ThreadData;

class PhotonMap;
struct Blob_Interval_Struct;

/**
 *  Class holding parser thread specific data.
 */
class SceneThreadData : public Task::TaskData
{
        friend class Scene;
        friend class Trace;
        friend class View; // TODO FIXME - needed only to access TraceThreadData for CheckCameraHollowObject()
    public:
        /**
         *  Create thread local data.
         *  @param  sd              Scene data defining scene attributes.
         *  @param  seed            Seed for the stochastic random number generator;
         *                          should be unique for each thread and each render.
         */
        SceneThreadData(shared_ptr<SceneData> sd, size_t seed);

        /**
         *  Get the statistics.
         *  @return                 Reference to statistic counters.
         */
        RenderStatistics& Stats(void) { return renderStats; }

        DBL *Fractal_IStack[4];
        BBoxPriorityQueue Mesh_Queue;
        void **Blob_Queue;
        unsigned int Max_Blob_Queue_Size;
        DBL *Blob_Coefficients;
        Blob_Interval_Struct *Blob_Intervals;
        int Blob_Coefficient_Count;
        int Blob_Interval_Count;
        ISO_ThreadData *isosurfaceData;
        void *BCyl_Intervals;
        void *BCyl_RInt;
        void *BCyl_HInt;
        IStackPool stackPool;
        FPUContext *functionContext;
        vector<FPUContext *> functionPatternContext;
        int Facets_Last_Seed;
        int Facets_CVC;
        Vector3d Facets_Cube[81];

        /// Common random number generator for all stochastic stuff
        SeedableDoubleGeneratorPtr stochasticRandomGenerator;

        // TODO FIXME - thread-local copy of lightsources. we need this
        // because various parts of the lighting code seem to make changes
        // to the lightsource object passed to them (this is not confined
        // just to the area light shadow code). This code ought to be fixed
        // to treat the lightsource as const, after which this can go away.
        vector<LightSource *> lightSources;

        // all of these are for photons
        // most of them should be refactored into parameters, return values, or other objects
        LightSource *photonSourceLight;
        ObjectPtr photonTargetObject;
        bool litObjectIgnoresPhotons;
        MathColour GFilCol;
        int hitObject;    // did we hit the target object? (for autostop)
        DBL photonSpread; // photon spread (in radians)
        DBL photonDepth;  // total distance from light to intersection
        int passThruThis;           // is this a pass-through object encountered before the target?
        int passThruPrev;           // was the previous object a pass-through object encountered before the target?
        bool Light_Is_Global;       // is the current light global? (not part of a light_group?)
        PhotonMap* surfacePhotonMap;
        PhotonMap* mediaPhotonMap;

        CrackleCache mCrackleCache;

        // data for waves and ripples pattern
        unsigned int numberOfWaves;
        vector<double> waveFrequencies;
        vector<Vector3d> waveSources;

        /**
         * called after a rectangle is finished
         * used for crackle cache expiry
         */
        void AfterTile();

        /**
         * used by the crackle pattern to indicate age of cache entries
         * @return  the index of the current rectangle rendered
         */
        inline size_t ProgressIndex() const { return progress_index; }

        enum TimeType
        {
            kUnknownTime,
            kParseTime,
            kBoundingTime,
            kPhotonTime,
            kRadiosityTime,
            kRenderTime,
            kMaxTimeType
        };

        TimeType timeType;
        POV_LONG cpuTime;
        POV_LONG realTime;
        QualityFlags qualityFlags; // TODO FIXME - remove again

        inline shared_ptr<const SceneData> GetSceneData() const { return sceneData; }

    protected:
        /// scene data
        shared_ptr<SceneData> sceneData;
        /// render statistics
        RenderStatistics renderStats;

    private:
        /// not available
        SceneThreadData();

        /// not available
        SceneThreadData(const SceneThreadData&);

        /// not available
        SceneThreadData& operator=(const SceneThreadData&);

        /// current number of Tiles to expire crackle cache entries after
        size_t CrCache_MaxAge;
        /// current tile index (for crackle cache expiry)
        size_t progress_index;

    public: // TODO FIXME - temporary workaround [trf]

        /**
         *  Destructor.
         */
        ~SceneThreadData();
};

/**
 *  Class holding render thread specific data.
 */
class ViewThreadData : public SceneThreadData
{
        friend class Scene;
    public:
        /**
         *  Create thread local data.
         *  @param  vd              View data defining view attributes
         *                          as well as view output.
         *  @param  seed            Seed for the stochastic random number generator;
         *                          should be unique for each thread and each render.
         */
        ViewThreadData(ViewData *vd, size_t seed);

        /**
         *  Get width of view.
         *  @return                 Width.
         */
        unsigned int GetWidth() const;

        /**
         *  Get height of view.
         *  @return                 Height.
         */
        unsigned int GetHeight() const;

        /**
         *  Get area of view to be rendered.
         *  @return                 Area rectangle.
         */
        const POVRect& GetRenderArea();
    protected:
        /// view data
        ViewData *viewData;
    private:
        /// not available
        ViewThreadData();

        /// not available
        ViewThreadData(const ViewThreadData&);

        /// not available
        ViewThreadData& operator=(const ViewThreadData&);
    public: // TODO FIXME - temporary workaround [trf]
        /**
         *  Destructor.
         */
        ~ViewThreadData();
};

}

#endif // POVRAY_BACKEND_THREADDATA_H
