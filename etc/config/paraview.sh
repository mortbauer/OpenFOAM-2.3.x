#----------------------------------*-sh-*--------------------------------------
# =========                 |
# \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
#  \\    /   O peration     |
#   \\  /    A nd           | Copyright (C) 2011-2014 OpenFOAM Foundation
#    \\/     M anipulation  |
#------------------------------------------------------------------------------
# License
#     This file is part of OpenFOAM.
#
#     OpenFOAM is free software: you can redistribute it and/or modify it
#     under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
#
#     OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
#     ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#     FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
#     for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.
#
# File
#     config/paraview.sh
#
# Description
#     Setup file for paraview-[3-4].x
#     Sourced from OpenFOAM-<VERSION>/etc/bashrc or from foamPV alias
#
# Note
#     The env. variables 'ParaView_DIR' and 'ParaView_MAJOR'
#     are required for building plugins
#------------------------------------------------------------------------------


#- ParaView version, automatically determine major version
export ParaView_VERSION=4.2.0
export ParaView_MAJOR=4.2


paraviewInstDir=$WM_THIRD_PARTY_DIR/ParaView-$ParaView_VERSION
paraviewArchName=ParaView-$ParaView_VERSION

export ParaView_DIR=/usr
export ParaView_INCLUDE_DIR=$ParaView_DIR/include/paraview-$ParaView_MAJOR
ParaView_LIB_DIR=$ParaView_DIR/lib/paraview-$ParaView_MAJOR

export PATH=$ParaView_DIR/bin:$PATH
export LD_LIBRARY_PATH=$ParaView_LIB_DIR:$LD_LIBRARY_PATH
export PV_PLUGIN_PATH=$FOAM_LIBBIN/paraview-$ParaView_MAJOR

# # add in python libraries if required
    #paraviewPython=$ParaView_DIR/Utilities/VTKPythonWrapping
    #if [ -r $paraviewPython ]
    #then
        #if [ "$PYTHONPATH" ]
        #then
            #export PYTHONPATH=$PYTHONPATH:$paraviewPython:$ParaView_LIB_DIR

## set paths if binaries or source are present
#if [ -r $ParaView_DIR -o -r $paraviewInstDir ]
#then
    #export ParaView_INCLUDE_DIR=$ParaView_DIR/include/paraview-$ParaView_MAJOR
    #if [ ! -d $ParaView_INCLUDE_DIR -a -d $ParaView_DIR/include/paraview ]
    #then
        #export ParaView_INCLUDE_DIR=$ParaView_DIR/include/paraview
    #fi

    #ParaView_LIB_DIR=$ParaView_DIR/lib/paraview-$ParaView_MAJOR
    #if [ ! -d $ParaView_LIB_DIR -a -d $ParaView_DIR/lib/paraview ]
    #then
        #ParaView_LIB_DIR=$ParaView_DIR/lib/paraview
    #fi

    #export PATH=$ParaView_DIR/bin:$PATH
    #export LD_LIBRARY_PATH=$ParaView_LIB_DIR:$LD_LIBRARY_PATH
    #export PV_PLUGIN_PATH=$FOAM_LIBBIN/paraview-$ParaView_MAJOR

    #if [ "$FOAM_VERBOSE" -a "$PS1" ]
    #then
        #echo "Using paraview"
        #echo "    ParaView_DIR         : $ParaView_DIR"
        #echo "    ParaView_LIB_DIR     : $ParaView_LIB_DIR"
        #echo "    ParaView_INCLUDE_DIR : $ParaView_INCLUDE_DIR"
        #echo "    PV_PLUGIN_PATH       : $PV_PLUGIN_PATH"
    #fi

    ## add in python libraries if required
    #paraviewPython=$ParaView_DIR/Utilities/VTKPythonWrapping
    #if [ -r $paraviewPython ]
    #then
        #if [ "$PYTHONPATH" ]
        #then
            #export PYTHONPATH=$PYTHONPATH:$paraviewPython:$ParaView_LIB_DIR
        #else
            #export PYTHONPATH=$paraviewPython:$ParaView_LIB_DIR
        #fi
    #fi
#else
    #unset PV_PLUGIN_PATH
#fi


# -----------------------------------------------------------------------------
