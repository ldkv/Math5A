#pragma once

#include <QGLWidget>

using namespace std;

vector<QPoint> calculateCasteljau(vector<QPoint> poly, double a, double b, int nbPas);
QPoint getCasteljauPoint(vector<QPoint> poly, int r, int i, double t);
vector<QPoint> calculateCornerCutting(int pointSelect, vector<QPoint> poly, vector<int> r, int nbPas);
vector<QPoint> generateCourbeCC(int pointSelect, vector<QPoint> corners, double a, double b, vector<int> r, int nbPas);
QPoint findMediumPoint(QPoint P1, QPoint P2, int r1, int r2);