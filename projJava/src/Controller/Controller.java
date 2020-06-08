package Controller;

import Modelo.Crono;
import Modelo.Model;
import View.View;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.Serializable;
import java.util.List;
import java.util.Scanner;

/**
 * Classe que contém a implementação do Interpretador
 */
public class Controller implements Serializable {


    /**
     * Função que dá ao utilizador a opção de introduzir ao seu gosto os parâmetros utilizados nas diversas funções
     * @throws FileNotFoundException
     * @throws ClassNotFoundException
     * @throws 
     */
    public void interpretador(View v, Model m) throws FileNotFoundException,ClassNotFoundException,IOException {
        int escolha;
        boolean flag = false;
        do {
            v.menu();
            Scanner num = new Scanner(System.in);
            escolha = num.nextInt();
            switch (escolha) {
                case 0:
                    m = new Model();
                    v.estrutura();
                    List<String> path = v.inicializacao();
                    String prodPath = path.get(0);
                    String cliPath = path.get(1);
                    String salesPath = path.get(2);
                    Crono.start();
                    m.loadSGV(prodPath,cliPath,salesPath);
                    v.tempo(Crono.getTimeString());
                    flag = true;
                    break;
                case 1:
                    if(!flag) {
                        v.naoInicializada();
                        break;
                    }
                    interativas(m);
                    break;
                case 2:
                    if(!flag) {
                        v.naoInicializada();
                        break;
                    }
                    estatisticas(m);
                    break;
                case 3:
                    if(!flag) {
                        v.naoInicializada();
                        break;
                    }
                    try {
                        Crono.start();
                        m.guardaEstado("GestaoVendas.dat");
                        v.tempo(Crono.getTimeString());
                    }catch (IOException e){
                        v.erroGravar();
                    }
                    break;
                case 4:
                    if(!flag) {
                        v.naoInicializada();
                        break;
                    }
                    try {
                        Crono.start();
                        String nome = v.nomeFicheiroBinario();
                        m = m.carregaEstado(nome);
                        v.tempo(Crono.getTimeString());
                    }catch (IOException | ClassNotFoundException e){
                        v.erroLer();
                    }
                    break;
            }
        }
        while (escolha != 5) ;
    }

    /**
     * Função que permite ao utilizador escolher qual consulta interativa quer ver
     * @param m        Sistema de Gestão de Vendas
     */
    public void interativas(Model m){
        View v = new View();
        int escolha;
        do {
            v.interativas();
            Scanner num = new Scanner(System.in);
            escolha = num.nextInt();
            switch(escolha){
                case 1:
                    v.printQuerie1(m);
                    break;
                case 2:
                    v.printQuerie2(m);
                    break;
                case 3:
                    v.printQuerie3(m);
                    break;
                case 4:
                    v.printQuerie4(m);
                    break;
                case 5:
                    v.printQuerie5(m);
                    break;
                case 6:
                    v.printQuerie6(m);
                    break;
                case 7:
                    v.printQuerie7(m);
                    break;
                case 8:
                    v.printQuerie8(m);
                    break;
                case 9:
                    v.printQuerie9(m);
                    break;
                case 10:
                    v.printQuerie10(m);
                    break;
            }
        }
        while(escolha!=11);
    }


    /**
     * Função que permite ao utilizador escolher qual consulta estatistica quer ver
     * @param m          Sistema de Gestão de Vendas
     */
    public void estatisticas(Model m){
        int escolha;
        View v = new View();
        do {
            v.estatisticas();
            Scanner num = new Scanner(System.in);
            escolha = num.nextInt();
            switch(escolha) {
                case 1:
                    v.printconsulta1(m);
                    break;
                case 2:
                    v.printconsulta2(m);
                    break;
            }
        }
        while(escolha!=3);
    }


}