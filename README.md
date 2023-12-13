# GLCube
DirectX cube, but it's done using OpenGL. This is a quaternion rotation test.

This is a recreation of the old Direct 3D test animation, which displayed a rotating cube with the DirectX logo on it. The rotation in this version is done using a quaternion transformation. You can learn more about quaternion rotations in the following links:

[(Danceswithcode.net) Quaternions](https://danceswithcode.net/engineeringnotes/quaternions/quaternions.html)
[Wikipedia - Quaternion](https://en.wikipedia.org/wiki/Quaternion)

Quaternions are not easy to understand at a mathematical level, but in practice, all you have is a vector defining an axis of rotation, and the angle of rotation around that vector.

The function getRotationMatrixFromQuaternion() creates a rotation matrix from a vector given it's x,y,z components and the angle of rotation theta, and then tells OpenGL to use it as it's rotation matrix for the cube.

Quaternions are used to avoid gimbal lock by providing an additional axis of movement, rather than rotating over the axes in the object's space.

DirectX is copyrighted by the Microsoft Corporation and they are the ones who have the copyright on it. This project is provided for free. The assets used in this projects were recreated for it, no assets have been ripped from the original software.

Requires [libenigl](https://github.com/aaroncdc/libenigl) .