/**
 *  \author    : zeillah
 *  \version   : 1.0
 *  \date      : 25.04.2015
 */

#include "Scene.h"
#include "src/io/ObjReader.h"

Scene::Scene(int width, int height, const QString &modelPath, QOpenGLShaderProgram *vcp, QOpenGLShaderProgram *mp)
{
    vertexcolorProgram = vcp;
    modelProgram = mp;

    //camera = new Camera(width, height, QVector3D(0, 0, -2.5), QVector3D(0, 0, 1), QVector3D(0, 1, 0));
    camera = new Camera(width, height, QVector3D(0, 0, 2.5), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
    lightSources.push_back(Light( QVector3D(0.5, 0.0, 0.0),  QVector4D(1.0, 1.0, 1.0, 1.0), 0.1, 0.2) );
    lightSources.push_back(Light( QVector3D(0.0, -0.5, 0.0),  QVector4D(1.0, 1.0, 1.0, 1.0), 0.1, 0.2) );
    lightSources.push_back(Light( QVector3D(0.0, 0.0, 0.3),  QVector4D(1.0, 1.0, 1.0, 1.0), 0.1, 0.2) );

    Mesh mesh = ObjReader::initGeometryFromObjFile(modelPath);
    model = new Model(mesh);
    axes = new Axes();
    showingTriangles = false;
    highlightHoles   = false;
}

void Scene::render()
{
    renderAxes();
    renderModel();

}

void Scene::init()
{
    // initialize geometry
    axes->init();
    model->init();
}

void Scene::loadObject(QString &filename)
{
    Mesh mesh = ObjReader::initGeometryFromObjFile(filename);
    model = new Model(mesh);
    model->init();
}

void Scene::updateMaterial(shared_ptr<Material> material)
{
    model->setMaterial(material);
}

void Scene::smoothModel(int iterations)
{
    model->smooth(iterations);
}

void Scene::decimateModel(float percent)
{
    model->decimate(percent);
}

void Scene::subdivideModel(const QString &method, float numSubdivisions)
{
    model->subdivide(method, numSubdivisions);
}

void Scene::renderAxes()
{
    glEnable(GL_DEPTH_TEST);

    QMatrix4x4 modelViewProjection = camera->projection * camera->lookAtMat * currentTranslation * currentRotation;

    vertexcolorProgram->bind();
    vertexcolorProgram->setUniformValue("uMVPMatrix", modelViewProjection);
    vertexcolorProgram->setUniformValue("uAlpha", 1.0f);

    glEnable(GL_BLEND);
    axes->draw(vertexcolorProgram);
    glDisable(GL_BLEND);
}

void Scene::renderModel()
{
    QMatrix4x4 modelView = calculateModelViewMatrix();
    QMatrix4x4 modelViewProjection = camera->projection * modelView;
    QMatrix3x3 normalMatrix = modelView.normalMatrix();

    modelProgram->bind();
    modelProgram->setUniformValue("uMVMatrix", modelView);
    modelProgram->setUniformValue("uMVPMatrix", modelViewProjection);
    modelProgram->setUniformValue("uNormalMatrix", normalMatrix);

    modelProgram->setUniformValue("numLights", (int)lightSources.size());
    for(size_t i = 0; i < lightSources.size(); i++) {
        setLightUniform(modelProgram, "position", i, lightSources[i].position);
        setLightUniform(modelProgram, "color", i, lightSources[i].color);
        setLightUniform(modelProgram, "ambientCoefficient", i, lightSources[i].ambientCoefficient);
        setLightUniform(modelProgram, "attenuation", i, lightSources[i].attenuation);
    }
    modelProgram->setUniformValue("uEye", camera->eye.normalized());
    modelProgram->setAttributeValue("ambientMaterial", model->getMaterial()->ambient);
    modelProgram->setAttributeValue("diffuseMaterial", model->getMaterial()->diffuse);
    modelProgram->setAttributeValue("specularMaterial", model->getMaterial()->specular);
    modelProgram->setAttributeValue("shininess", model->getMaterial()->shininess);

    modelProgram->setAttributeArray("edgeVertices", model->getEdgeVertices().data());

    glDisable(GL_CULL_FACE);
    if(showingTriangles) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
    }

    model->draw(modelProgram);
    glEnable(GL_CULL_FACE);
}

QMatrix4x4 Scene::calculateModelViewMatrix()
{
    QMatrix4x4 modelMatrix;
    // - scaling
    QMatrix4x4 scale;
    scale.scale(model->getScaling());

    // - create model matrix and move to world coordinate origin
    modelMatrix = currentTranslation * currentRotation * scale * modelMatrix;

    QVector3D centroid = model->getCentroid();
    modelMatrix.translate(-centroid);

    // - view, MV and MVP matrices
    QMatrix4x4 viewMatrix = camera->lookAtMat;

    return viewMatrix * modelMatrix;
}

template <typename T>
void Scene::setLightUniform(QOpenGLShaderProgram *program, const char* propertyName, size_t lightIndex, const T& value)
{
    std::ostringstream ostr; //output string stream
    ostr << "allLights[" << lightIndex << "]." << propertyName;
    std::string uniformName = ostr.str();
    program->setUniformValue(uniformName.c_str(), value);
}