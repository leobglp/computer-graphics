#ifndef FORMAFACTORY_H
#define FORMAFACTORY_H

#include <QString>
#include <QColor>
#include <QMap>
#include <functional>
#include <memory>

#include "Ponto.h"
#include "Reta.h"
#include "Triangulo.h"
#include "Quadrado.h"
#include "Circunferencia.h"

// Design Pattern -> Factory: gerencia registro e criação de formas
class FormaFactory {
public:
    using CriadorFormaSimples = std::function<ObjetoGrafico*(double x, double y, const QColor&)>;
    using CriadorFormaComplexa = std::function<ObjetoGrafico*(double x1, double y1, double x2, double y2, const QColor&)>;
    using CriadorFormaTriangulo = std::function<ObjetoGrafico*(double x1, double y1, double x2, double y2, double x3, double y3, const QColor&)>;
    using CriadorFormaCircunferencia = std::function<ObjetoGrafico*(double x1, double y1, double raio, const QColor&)>;

    static FormaFactory& instance() {
        static FormaFactory inst;
        return inst;
    }

    void registrarSimples(const QString& nome, CriadorFormaSimples criador) {
        formasSimples[nome] = criador;
    }

    void registrarComplexa(const QString& nome, CriadorFormaComplexa criador) {
        formasComplexas[nome] = criador;
    }

    void registrarTriangulo(const QString& nome, CriadorFormaTriangulo criador) {
        formasTriangulo[nome] = criador;
    }

    void registrarCircunferencia(const QString& nome, CriadorFormaCircunferencia criador) {
        formasCircunferencia[nome] = criador;
    }

    QStringList nomesFormas() const {
        QStringList nomes = formasSimples.keys();
        nomes.append(formasComplexas.keys());
        nomes.append(formasTriangulo.keys());
        nomes.append(formasCircunferencia.keys());
        return nomes;
    }

    // Métodos separados para criar cada tipo de forma:

    ObjetoGrafico* criarSimples(const QString& nome, double x, double y, const QColor& cor) {
        if (formasSimples.contains(nome)) {
            return formasSimples[nome](x, y, cor);
        }
        return nullptr;
    }

    ObjetoGrafico* criarComplexa(const QString& nome, double x1, double y1, double x2, double y2, const QColor& cor) {
        if (formasComplexas.contains(nome)) {
            return formasComplexas[nome](x1, y1, x2, y2, cor);
        }
        return nullptr;
    }

    ObjetoGrafico* criarTriangulo(const QString& nome, double x1, double y1, double x2, double y2, double x3, double y3, const QColor& cor) {
        if (formasTriangulo.contains(nome)) {
            return formasTriangulo[nome](x1, y1, x2, y2, x3, y3, cor);
        }
        return nullptr;
    }

    ObjetoGrafico* criarCircunferencia(const QString& nome, double x1, double y1, double raio, const QColor& cor) {
        if (formasCircunferencia.contains(nome)) {
            return formasCircunferencia[nome](x1, y1, raio, cor);
        }
        return nullptr;
    }

private:
    FormaFactory() = default; // Construtor privado para Singleton

    QMap<QString, CriadorFormaSimples> formasSimples;
    QMap<QString, CriadorFormaComplexa> formasComplexas;
    QMap<QString, CriadorFormaTriangulo> formasTriangulo;
    QMap<QString, CriadorFormaCircunferencia> formasCircunferencia;
};

#endif // FORMAFACTORY_H
