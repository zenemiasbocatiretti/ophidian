/*
 * Copyright 2017 Ophidian
   Licensed to the Apache Software Foundation (ASF) under one
   or more contributor license agreements.  See the NOTICE file
   distributed with this work for additional information
   regarding copyright ownership.  The ASF licenses this file
   to you under the Apache License, Version 2.0 (the
   "License"); you may not use this file except in compliance
   with the License.  You may obtain a copy of the License at
   http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing,
   software distributed under the License is distributed on an
   "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
   KIND, either express or implied.  See the License for the
   specific language governing permissions and limitations
   under the License.
 */

#ifndef OPHIDIAN_PLACEMENT_LIBRARY_H
#define OPHIDIAN_PLACEMENT_LIBRARY_H

#include <ophidian/entity_system/EntitySystem.h>
#include <ophidian/entity_system/Property.h>
#include <ophidian/geometry/Models.h>
#include <ophidian/standard_cell/StandardCells.h>
#include <ophidian/util/Units.h>

namespace ophidian
{
    namespace placement
    {
        class Library
        {
        public:

            //! Library Copy Constructor

            /*!
               \brief Constructs a placement library.
             */
            Library(const standard_cell::StandardCells & std_cells);

            //! Cell geometry getter

            /*!
               \brief Gets the geometry of a cell.
               \param cell Cell entity to get the geometry.
               \return Geometry of the cell.
             */
            geometry::MultiBox geometry(const standard_cell::Cell & cell) const
            {
                return mGeometries[cell];
            }

            //! Cell geometry setter

            /*!
               \brief Set the geometry of a cell.
               \param cell Cell entity to set the geometry.
               \param geometry Gehmetry to assign to cell.
             */
            void geometry(const standard_cell::Cell & cell, const geometry::MultiBox & geometry);

            //! Pin offset getter

            /*!
               \brief Gets the offset of a pin.
               \param pin Pin entity to get the offset.
               \return Offset of the pin.
             */
            util::LocationDbu pinOffset(const standard_cell::Pin & pin) const
            {
                return mPinOffsets[pin];
            }

            //! Pin offset setter

            /*!
               \brief Sets the offset of a pin.
               \param pin Pin entity to set the offset.
               \param offset Offset to assign to pin.
             */
            void pinOffset(const standard_cell::Pin & pin, const util::LocationDbu & offset);

        private:
            entity_system::Property <standard_cell::Cell, geometry::MultiBox> mGeometries;
            entity_system::Property <standard_cell::Pin, util::LocationDbu>   mPinOffsets;
        };
    }     // namespace placement
}     // namespace ophidian

#endif // LIBRARY_H