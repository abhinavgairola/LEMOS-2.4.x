/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | Unsupported Contributions for OpenFOAM
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2013 LEMOS, University Rostock
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is a derivative work of OpenFOAM.

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
    Foam::volWeightedGaussianFilter

Description
    Gaussian filter using volume sampled gaussian kernel and point connected cell stencil. 
 
SourceFiles
    volWeightedGaussianFilter.C

\*---------------------------------------------------------------------------*/

#ifndef volWeightedGaussianFilter_H
#define volWeightedGaussianFilter_H

#include "LESfilter.H"
#include "centredCPCCellToCellExtStencilObject.H"
#include "volFields.H"
#include "PtrList.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class legendreFilter Declaration
\*---------------------------------------------------------------------------*/

class volWeightedGaussianFilter
:
    public LESfilter

{
    // Private Member Functions

        //- Disallow default bitwise copy construct and assignment
        volWeightedGaussianFilter(const volWeightedGaussianFilter&);
        void operator=(const volWeightedGaussianFilter&);

        const extendedCentredCellToCellExtStencil& addressing_;

	//- Stencil weights 
	List<List<scalar> > stencilWeights_;

	//- Scaling factor gamma for gaussian
	scalar gamma_;

public:

    //- Runtime type information
    TypeName("volWeightedGaussianMean");


    // Constructors

        //- from components
        volWeightedGaussianFilter(const fvMesh& mesh, const scalar gamma);

        //- from IOdictionary
        volWeightedGaussianFilter(const fvMesh& mesh, const dictionary& dict);


    // Destructor
    virtual ~volWeightedGaussianFilter()
    {}



    // Member Functions

        //- Read the LESfilter dictionary
        void read(const dictionary& dict);

        //- Arrange element weights in stencil order 
        void stencilWeights();

        //- Update stencil and dependencies after mesh changing
        void updateStencil();

    // Member Operators
    
        virtual tmp<volScalarField> operator()
	(
	    const tmp<volScalarField>&
	) const;

        virtual tmp<volVectorField> operator()
	(
	    const tmp<volVectorField>&
	) const;

        virtual tmp<volSymmTensorField> operator()
        (
            const tmp<volSymmTensorField>&
        ) const;

        virtual tmp<volTensorField> operator()
	(
	    const tmp<volTensorField>&
	) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
