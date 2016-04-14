/**
 *  \author    : zeillah
 *  \version   : 1.0
 *  \date      : 25.04.2015
 */

#ifndef OPENGLVIEWER_SCENE_H
#define OPENGLVIEWER_SCENE_H

#include <QtOpenGL>
#include <QOpenGLShaderProgram>
#include "src/models/Axes.h"
#include "src/models/Model.h"
#include "src/scene/Camera.h"
#include "src/models/Material.h"
#include "src/scene/Light.h"

class Scene {

    public:
        Scene(int width, int height, const QString &modelPath, QOpenGLShaderProgram *vcp, QOpenGLShaderProgram *mp);
        void init();
        void render();

        void updateScaling(float scaleFactor) { camera->updatePerspective(scaleFactor); }
        void updateTranslation(const QMatrix4x4 &translation) { currentTranslation = translation; };
        void updateRotation(const QMatrix4x4 &rotation) { currentRotation = rotation; };

        void loadObject(QString &filename);
        void updateMaterial(shared_ptr<Material> material);


        void smoothModel(int iterations);
        void decimateModel(float percent);
        void subdivideModel(const QString &method, float numSubdivisions);


        void showTriangles(bool show) { showingTriangles = show; };
        void showHoles(bool show) { highlightHoles = show; };

    private:
        QOpenGLShaderProgram *vertexcolorProgram;
        QOpenGLShaderProgram *modelProgram;
        bool showingTriangles;
        bool highlightHoles;

        Axes *axes;
        Model *model;
        Camera *camera;
        vector<Light> lightSources;

        QMatrix4x4 currentTranslation;
        QMatrix4x4 currentRotation;

        void renderAxes();
        void renderModel();
        QMatrix4x4 calculateModelViewMatrix();
        template <typename T>
        void setLightUniform(QOpenGLShaderProgram *program, const char* propertyName, size_t lightIndex, const T& value);
};


#endif //OPENGLVIEWER_SCENE_H
