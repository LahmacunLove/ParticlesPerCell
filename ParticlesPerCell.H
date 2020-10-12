/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::ParticlesPerCell

Group
    grpLagrangianIntermediateFunctionObjects

Description
    Creates particle concentration in particles per cell

SourceFiles
    ParticlesPerCell.C

\*---------------------------------------------------------------------------*/

#ifndef ParticlesPerCell_H
#define ParticlesPerCell_H

#include "CloudFunctionObject.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                       Class ParticlesPerCell Declaration
\*---------------------------------------------------------------------------*/

template<class CloudType>
class ParticlesPerCell
:
    public CloudFunctionObject<CloudType>
{
    // Private Data

        // Typedefs

            //- Convenience typedef for parcel type
            typedef typename CloudType::parcelType parcelType;


        //- Void fraction field
        autoPtr<volScalarField> thetaPtr_;


protected:

    // Protected Member Functions

        //- Write post-processing info
        virtual void write();


public:

    //- Runtime type information
    TypeName("particlesPerCell");


    // Constructors

        //- Construct from dictionary
        ParticlesPerCell
        (
            const dictionary& dict,
            CloudType& owner,
            const word& modelName
        );

        //- Construct copy
        ParticlesPerCell(const ParticlesPerCell<CloudType>& vf);

        //- Construct and return a clone
        virtual autoPtr<CloudFunctionObject<CloudType>> clone() const
        {
            return autoPtr<CloudFunctionObject<CloudType>>
            (
                new ParticlesPerCell<CloudType>(*this)
            );
        }


    //- Destructor
    virtual ~ParticlesPerCell() = default;


    // Member Functions

        // Evaluation

            //- Pre-evolve hook
            virtual void preEvolve
            (
                const typename parcelType::trackingData& td
            );

            //- Post-evolve hook
            virtual void postEvolve
            (
                const typename parcelType::trackingData& td
            );

            //- Post-move hook
            virtual void postMove
            (
                parcelType& p,
                const scalar dt,
                const point& position0,
                bool& keepParticle
            );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "ParticlesPerCell.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
