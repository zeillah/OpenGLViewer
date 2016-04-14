/**
 *  \author    : Nicole Schmelzer
 *  \version   : 1.0
 *  \date      : 13.06.15
 */

#include "ObjReader.h"
using namespace std;

Mesh ObjReader::initGeometryFromObjFile(QString _filename)
{
    Mesh mesh;
    mesh.request_vertex_normals();

    // - for collapsing edges
    mesh.request_vertex_status();
    mesh.request_edge_status();
    mesh.request_face_status();

    OpenMesh::IO::Options readOptions;
    cout << "reading mesh" << endl;

    if (!OpenMesh::IO::read_mesh(mesh,_filename.toStdString(), readOptions))
    {
        std::cerr << "read error\n";
        exit(1);
    }

    // If the file did not provide vertex normals, then calculate them
    if ( !readOptions.check( OpenMesh::IO::Options::VertexNormal ) )
    {
        // we need face normals to update the vertex normals
        mesh.request_face_normals();
        // let the mesh update the normals
        mesh.update_normals();
        // dispose the face normals, as we don't need them anymore
        mesh.release_face_normals();
    }

    return mesh;
}
