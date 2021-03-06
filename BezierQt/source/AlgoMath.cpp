#include "AlgoMath.h"

// G�n�ration de la courbe de B�zier par l'algorithme de Casteljau
vector<QPoint> calculateCasteljau(vector<QPoint> poly, double a, double b, int nbPas)
{
	vector<QPoint> bezier;
	if (poly.size() > 0)
	{
		double pas = (b - a) / nbPas;
		for (double t = a; t <= b; t += pas)
			bezier.push_back(getCasteljauPoint(poly, poly.size() - 1, 0, t));
	}
	return bezier;
}

// Fonction interm�diaire pour l'algo de Casteljau
QPoint getCasteljauPoint(vector<QPoint> poly, int r, int i, double t)
{
	if (r == 0) return poly[i];
	QPoint p1 = getCasteljauPoint(poly, r - 1, i, t);
	QPoint p2 = getCasteljauPoint(poly, r - 1, i + 1, t);
	return QPoint((int)((1 - t) * p1.x() + t * p2.x()), (int)((1 - t) * p1.y() + t * p2.y()));
}

// D�termination des nouveau points de contr�le pour la m�thode Corner Cutting
vector<QPoint> calculateCornerCutting(int pointSelect, vector<QPoint> poly, vector<int> r, int nbPas)
{
	vector<QPoint> corners;
	int nbPoints = poly.size();
	if (pointSelect <= 0 || pointSelect == nbPoints - 1)
	{
		if (nbPoints >= 5)
		{
			QPoint Q1, Q2, R1, R2;
			
			corners.push_back(poly[0]);
			corners.push_back(poly[1]);
			Q1 = findMediumPoint(poly[1], poly[2], r[0], r[1]);
			Q2 = findMediumPoint(poly[2], poly[3], r[0], r[1] + r[2]);
			corners.push_back(Q1);
			corners.push_back(findMediumPoint(Q1, Q2, r[0], r[1]));
			Q1 = Q2;
			R1 = findMediumPoint(Q1, poly[3], r[1], r[2]);
			for (int i = 3; i < nbPoints - 2; i++)
			{
				Q2 = findMediumPoint(poly[i], poly[i + 1], r[i - 2], r[i - 1] + r[i]);
				R2 = findMediumPoint(Q2, poly[i + 1], r[i - 1], r[i]);
				corners.push_back(Q1);
				corners.push_back(R1);
				corners.push_back(findMediumPoint(R1, Q2, r[0], r[1]));
				Q1 = Q2;
				R1 = R2;
			}
			Q1 = findMediumPoint(poly[nbPoints - 3], poly[nbPoints - 2], r[nbPoints - 4], r[nbPoints - 3]);
			corners.push_back(Q1);
			corners.push_back(poly[nbPoints - 2]);
			corners.push_back(poly[nbPoints - 1]);
		}
	}
	else if (nbPoints >= 5)
	{
		if (pointSelect == 1)
		{
			QPoint Q1 = findMediumPoint(poly[1], poly[2], r[0], r[1]);
			QPoint Q2 = findMediumPoint(poly[2], poly[3], r[0], r[1] + r[2]);
			QPoint R1, R2;
		}
	}
	return corners;
}

// Engendrement spline cubique C2 par la m�thode Corner Cutting
vector<QPoint> generateCourbeCC(int pointSelect, vector<QPoint> corners, double a, double b, vector<int> r, int nbPas)
{
	vector<QPoint> courbes;
	int nbPoints = corners.size();
	for (int i = 0; i < nbPoints - 3; i += 3)
	{
		vector<QPoint> poly4;
		poly4.push_back(corners[i]);
		poly4.push_back(corners[i + 1]);
		poly4.push_back(corners[i + 2]);
		poly4.push_back(corners[i + 3]);

		vector<QPoint> bezier3 = calculateCasteljau(poly4, a, b, nbPas);
		int nbPts = bezier3.size();
		for (int j = 0; j < nbPts; j++)
			courbes.push_back(bezier3[j]);
	}
	return courbes;
}

// Determination du point X o�: P1X * r2 = XP2 * r1
QPoint findMediumPoint(QPoint P1, QPoint P2, int r1, int r2)
{
	return P1 + (P2 - P1) * r1 / (r1+r2);
}