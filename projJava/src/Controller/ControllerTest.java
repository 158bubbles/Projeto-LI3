package Controller;

import Modelo.Model;
import View.ViewTest;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

public class ControllerTest {

    public void interpretador(ViewTest v, Model m) throws FileNotFoundException,ClassNotFoundException, IOException {
        int escolha;
        String prodPath = "DadosIniciais/Produtos.txt";
        String cliPath = "DadosIniciais/Clientes.txt";
        String path1M = "DadosIniciais/Vendas_1M.txt";
        String path3M = "DadosIniciais/Vendas_3M.txt";
        String path5M = "DadosIniciais/Vendas_5M.txt";
        m.loadSGV(prodPath, cliPath, path1M);
        do {
            v.menu();
            Scanner num = new Scanner(System.in);
            escolha = num.nextInt();
            switch (escolha) {
                case 1:
                    v.test1(path1M, path3M, path5M, m);
                    break;
                case 2:
                    v.test2(path1M,path3M,path5M,m);
                    break;
                case 3:
                    v.test3(path1M,path3M,path5M,m);
                    break;
                case 4:
                    v.ficheiroM();
                    int ficheiro = num.nextInt();
                    if(ficheiro == 1);
                    else if(ficheiro == 2){
                        m.loadSGV(prodPath,cliPath,path3M);
                    }
                    else if(ficheiro == 3){
                        m.loadSGV(prodPath,cliPath,path5M);
                    }
                    int n;
                    do {
                        v.menuTest4();
                        n =  num.nextInt();
                        switch (n) {
                            case 5:
                                v.querie5Test(m);
                                break;
                            case 6:
                                v.querie6Test(m);
                                break;
                            case 7:
                                v.querie7Test(m);
                                break;
                            case 8:
                                v.querie8Test(m);
                                break;
                            case 9:
                                v.querie9Test(m);
                                break;
                        }
                    }while(n!=0);
            }
        } while (escolha != 5);
    }
}
