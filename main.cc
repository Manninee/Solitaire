/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                                 #
# Project: Korttipeli                                                       #
# Eetu Manninen eetu.manninen@tuni.fi                                       #
# Pasianssi. Peliohje löytyy tiedostosta kayttohje.txt                      #
#                                                                           #
#############################################################################
*/


#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
