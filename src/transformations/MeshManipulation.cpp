/**
 *  \author    : Nicole Schmelzer
 *  \version   : 1.0
 *  \date      : 16.06.15
 */

#include <QVector3D>
#include "MeshManipulation.h"

using namespace std;

std::vector<QVector3D> MeshManipulation::paint(Mesh &mesh)
{
    std::vector<QVector3D> vertexColors;

    Mesh::FaceIter fIt,fBegin;
    Mesh::FaceVertexIter fvIt;
    fBegin = mesh.faces_begin();

    // - go through faces
    for( fIt = fBegin ; fIt != mesh.faces_end() ; ++fIt)
    {
        // - go through vertices of face
        for (fvIt=mesh.fv_iter( *fIt ); fvIt.is_valid(); ++fvIt) {

            if(mesh.is_boundary(*fvIt)) {
                vertexColors.push_back(QVector3D(0.0, 1.0, 0.0));
            } else {
                vertexColors.push_back(QVector3D(1.0, 1.0, 1.0));
            }
        }
    }
    return vertexColors;
}

Mesh MeshManipulation::smooth(Mesh &mesh, int iterations)
{
    //return MeshManipulation::smooth_valence(mesh, iterations);
    //return MeshManipulation::smooth_length(mesh, iterations);
    return MeshManipulation::smoothOpenMesh(mesh, iterations);
}

Mesh MeshManipulation::collapse(Mesh &mesh, int numFaces)
{
    // - edge collapse
    return MeshManipulation::collapseOpenMesh(mesh, numFaces);

}

Mesh MeshManipulation::subdivision(Mesh &mesh, int numSubdivisions, const QString &method)
{
    if(method.compare("Loop") == 0) {
        return loopSubdivision(mesh, numSubdivisions);
    }
    if(method.compare("Sqrt3") == 0) {
        return sqrt3Subdivision(mesh, numSubdivisions);
    }
    return loopSubdivision(mesh, numSubdivisions);
}

Mesh MeshManipulation::smoothOpenMesh(Mesh &mesh, int iterations)
{
    OpenMesh::Smoother::JacobiLaplaceSmootherT< Mesh > smoother( mesh );
    smoother.initialize( OpenMesh::Smoother::SmootherT< Mesh >::
                         Tangential_and_Normal, //Tangential_and_Normal,
                         OpenMesh::Smoother::SmootherT< Mesh >::C1 );

    smoother.smooth( iterations );

    return mesh;
}

Mesh MeshManipulation::loopSubdivision(Mesh &mesh, int numSubdivisions)
{
    // Create subdivider and subdivide
    OpenMesh::Subdivider::Uniform::LoopT<Mesh> loopSubdivider;

    loopSubdivider(mesh, numSubdivisions, true);
    loopSubdivider.detach();
    mesh.request_face_normals();
    mesh.update_normals();

    return mesh;
}

Mesh MeshManipulation::sqrt3Subdivision(Mesh &mesh, int numSubdivisions)
{
    // Create subdivider and subdivide
    OpenMesh::Subdivider::Uniform::Sqrt3T<Mesh> sqrt3Subdivider;

    sqrt3Subdivider(mesh, numSubdivisions, true);
    sqrt3Subdivider.detach();
    mesh.request_face_normals();
    mesh.update_normals();

    return mesh;
}

Mesh MeshManipulation::collapseOpenMesh(Mesh &mesh, int numFaces)
{

    // ---------------------------------------- Decimater

    // Decimater type
    typedef OpenMesh::Decimater::DecimaterT< Mesh > Decimater;

    // Decimation Module Handle type
    typedef OpenMesh::Decimater::ModQuadricT< Mesh >::Handle HModQuadric;

    // ---------------------------------------- decimater setup

    Decimater   decimater(mesh);  // a decimater object, connected to a mesh
    HModQuadric hModQuadric;      // use a quadric module

    if(decimater.add( hModQuadric )) {
        std::cout << decimater.module( hModQuadric ).name() << std::endl;
        // the way to access the module
        decimater.initialize();       // let the decimater initialize the mesh and the
        // modules

        // do decimation
        decimater.decimate_to(numFaces);

        // - neccessary for further decimation
        mesh.garbage_collection();
    }
    else {
        cout << "Could not add module" << endl;
    }


    return mesh;
}

Mesh MeshManipulation::smoothValence(Mesh &mesh, int iterations)
{

    // this vector stores the computed centers of gravity
    std::vector<Mesh::Point> cogs;
    std::vector<Mesh::Point>::iterator cog_it;
    cogs.reserve(mesh.n_vertices());

    Mesh::VertexIter v_it, v_end(mesh.vertices_end());
    Mesh::VertexVertexIter vv_it;
    Mesh::Point cog;
    Mesh::Scalar valence;

    for(int i = 0; i < iterations; i++) {

        cogs.clear();
        for (v_it = mesh.vertices_begin(); v_it != v_end; ++v_it) {
            cog[0] = cog[1] = cog[2] = valence = 0.0;

            for (vv_it = mesh.vv_iter(*v_it); vv_it.is_valid(); ++vv_it) {
                cog += mesh.point(*vv_it);
                ++valence;
            }
            cogs.push_back(cog / valence);
        }

        for (v_it = mesh.vertices_begin(), cog_it = cogs.begin(); v_it != v_end; ++v_it, ++cog_it) {
            if (!mesh.is_boundary(*v_it)) {
                mesh.set_point(*v_it, *cog_it);
            }
        }
    }

    return mesh;
}

Mesh MeshManipulation::smoothLength(Mesh &mesh, int iterations)
{
    std::vector<Mesh::Point>  cogs;
    std::vector<Mesh::Point>::iterator cog_it;
    cogs.reserve(mesh.n_vertices());

    Mesh::VertexIter vIt, vEnd(mesh.vertices_end());
    Mesh::VertexVertexIter vvIt;
    OpenMesh::Vec3f newP;
    float sum;

    for(int i = 0; i < iterations; i++) {
        cogs.clear();

        for( vIt = mesh.vertices_begin(); vIt != vEnd; ++vIt ) {
            newP[0] = newP[1] = newP[2] = sum = 0.0f;

            for(vvIt = mesh.vv_iter(*vIt); vvIt.is_valid(); ++vvIt) {
                OpenMesh::Vec3f vec = mesh.point(*vvIt) - mesh.point(*vIt);
                sum += (1.0f / vec.length());
                newP += (vec / vec.length());
            }
            OpenMesh::Vec3f l = sum * newP;
            cogs.push_back(l);
        }

        float lambda = 0.2f;
        Mesh::VertexIter v_it, v_end(mesh.vertices_end());
        for (v_it=mesh.vertices_begin(), cog_it=cogs.begin(); v_it!=v_end; ++v_it, ++cog_it){
            if ( !mesh.is_boundary( *v_it ) ) {
                OpenMesh::Vec3f oldP = mesh.point(*v_it);
                OpenMesh::Vec3f L = *cog_it;
                OpenMesh::Vec3f P = oldP + lambda * L;
                mesh.set_point( *v_it, P );
            }
        }
    }

    return mesh;
}