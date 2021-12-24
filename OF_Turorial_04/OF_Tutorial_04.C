/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
     \\/     M anipulation  |
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

Application
    OF_Tutorial_01

Description
    This is the OpenFOAM InfoTest tutorial from buaaymh.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    // Initialise OF case
    #include "setRootCase.H"

    Info << "vector test: " << nl
         << "zero:" << vector::zero << endl
         << "one :" << vector::one << endl
         << "dim:" << vector::dim << endl
         << "rank:" << vector::rank << nl << endl;

    vector d(0.5, 0.5, 0.5);
    Info << "vector: " << d << endl
         << "magnitude: " << mag(d) << endl
         << "unit: " << d / mag(d) << endl
         << "d * 3: " << d * 3 << endl
         << "d + d: " << d + d << endl
         << "d.dot(d): " << scalar(d & d) << endl
         << "d.cross(d): " << vector(d ^ d) << endl
         << "d.outer(d): " << d * d  << nl << endl;

    tensor t4(3, -2, 1, -2, 2, 0, 1, 0, 4);
    tensor t1(1, 2, 3, 4, 5, 6, 7, 8, 9);

    Info << "tensor test: " << endl
         << "tensor: " << t4 << endl
         << "inv: " << inv(t4) << endl
         << "I: " << (inv(t4) & t4) << endl
         << "x: " << t4.x() << endl
         << "y: " << t4.y() << endl
         << "z: " << t4.z() << endl
         << "T(): " << t1 + t1.T() << endl
         << "det: " << det(t4) << endl;

    scalar a[4] = {1.0, 2.0, 3.0, 4.0};
    List<scalar> list(a, a+4);
    Info << "List: " << list << endl;
    Info << "List + List: " << list + list << endl;
    Info << "List * 0: " << list * 0.0 << nl << endl;

    Info<< "End\n" << endl;

    return 0;
}

// ************************************************************************* //