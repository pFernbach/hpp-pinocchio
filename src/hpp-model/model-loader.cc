// Copyright (c) 2016, Joseph Mirabel
// Authors: Joseph Mirabel (joseph.mirabel@laas.fr)
//
// This file is part of hpp-pinocchio.
// hpp-pinocchio is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp-pinocchio is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp-pinocchio. If not, see <http://www.gnu.org/licenses/>.

#include <hpp/pinocchio/hpp-model/model-loader.hh>
#include <pinocchio/multibody/geometry.hpp>

/* Default path of the urdf file describing the robot to parse. */
const std::string urdfDefaultFilename =
       ROMEO_MODEL_DIR "/romeo_description/urdf/romeo_small.urdf";

/* Build a hpp::pinocchio::Device from urdf path. */
hpp::pinocchio::DevicePtr_t hppPinocchio( bool withGeoms, const std::string urdfFilename)
{
  hpp::pinocchio::DevicePtr_t pinocchio = hpp::pinocchio::Device::create(urdfFilename);
  hpp::pinocchio::ModelPtr_t model( new se3::Model() );
  se3::urdf::buildModel(urdfFilename,se3::JointModelFreeFlyer(),*model);
  pinocchio->model(model);
  pinocchio->createData();

  if( withGeoms )
    {
      std::vector<std::string> baseDirs; baseDirs.push_back(ROMEO_MODEL_DIR);
      hpp::pinocchio::GeomModelPtr_t geom( new se3::GeometryModel() );
      se3::urdf::buildGeom(pinocchio->model(),pinocchio->name(),se3::COLLISION,*geom,baseDirs);

      pinocchio->geomModel(geom);
      pinocchio->createGeomData();
    }

  return pinocchio;
}

