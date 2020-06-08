package View;

import Modelo.Model;
import Modelo.Crono;

import java.io.IOException;
import java.util.List;
import java.util.Map;
import java.util.Vector;

public class ViewTest {


    public void menu(){
        StringBuilder s = new StringBuilder();
        s.append("--------------- T E S T E S ---------------\n");
        s.append(" 1 - Sem parsing\n");
        s.append(" 2 - Com parsing e criacao de classe \n");
        s.append(" 3 - Com parsing e validacao \n");
        s.append(" 4 - Querie 5 - 9 \n");
        s.append(" 5 - Exit \n");
        s.append("Insira um comando :\n");
        System.out.println(s.toString());
    }

    public void test1(String path1M, String path3M, String path5M, Model m) throws IOException {
        Map.Entry<String,String> t1 = m.getV().vendasSemParsing(path1M);
        Map.Entry<String,String> t2 = m.getV().vendasSemParsing(path3M);
        Map.Entry<String,String> t3 = m.getV().vendasSemParsing(path5M);
        System.out.println(" ------------ Testes sem Parsing ------------\n");
        System.out.println("                                              BufferReader                   Files");
        System.out.println(path1M + "                   " + t1.getValue()+"        "+t1.getKey());
        System.out.println(path3M + "                   " + t2.getValue()+"        "+t2.getKey());
        System.out.println(path5M + "                   " + t3.getValue()+"        "+t3.getKey());
        System.out.println();
    }

    public void ficheiroM(){
        System.out.println("------------ Ficheiro ------------\n");
        System.out.println("1 - 1 Milhao");
        System.out.println("2 - 3 Milhoes");
        System.out.println("3 - 5 Milhoes");
    }

    public void test2(String path1M, String path3M, String path5M, Model m) throws IOException {
        String t1 = m.getV().vendasComParsing(path1M);
        String t2 = m.getV().vendasComParsing(path3M);
        String t3 = m.getV().vendasComParsing(path5M);
        System.out.println(" ------------ Testes com Parsing ------------\n");
        System.out.println("                                              Time");
        System.out.println(path1M + "                   " + t1);
        System.out.println(path3M + "                   " + t2);
        System.out.println(path5M + "                   " + t3);
        System.out.println();
    }

    public void test3(String path1M, String path3M, String path5M, Model m) throws IOException {
        String t1 = m.getV().vendasComParsingValidacao(m.getV(),m.getP().getProdutos(),m.getC().getClientes(),path1M);
        String t2 = m.getV().vendasComParsingValidacao(m.getV(),m.getP().getProdutos(),m.getC().getClientes(),path3M);
        String t3 = m.getV().vendasComParsingValidacao(m.getV(),m.getP().getProdutos(),m.getC().getClientes(),path5M);
        System.out.println(" ------------ Testes com Parsing e validacao ------------\n");
        System.out.println("                                              Time");
        System.out.println(path1M + "                   " + t1);
        System.out.println(path3M + "                   " + t2);
        System.out.println(path5M + "                   " + t3);
        System.out.println();
    }


    public void menuTest4(){
        StringBuilder s = new StringBuilder();
        s.append("--------------- Teste Querie 5 a 9 ---------------\n");
        s.append(" 5 - Querie 5\n");
        s.append(" 6 - Querie 6 \n");
        s.append(" 7 - Querie 7\n");
        s.append(" 8 - Querie 8\n");
        s.append(" 9 - Querie 9\n");
        s.append(" 0 - Exit\n");
        s.append("Insira um comando :\n");
        System.out.println(s.toString());
    }
    public void querie5Test(Model m1){
        Crono.start();
        List<String> q51M = m1.Querie5("Z5000");
        String tempQ51M = Crono.getTimeString();
        Crono.start();
        Vector<String> q5T1M = m1.Querie5Test("Z5000");
        String tempQ5T1M = Crono.getTimeString();
        System.out.println(" ------------------ Testes Querie 5  ------------------\n");
        System.out.println("Original                                  Alterado");
        System.out.println( tempQ51M+"               "+tempQ5T1M);
    }

    public void querie6Test(Model m1){
        Crono.start();
        Map<Integer,Map.Entry<String,Integer>> q1M = m1.Querie6(5);
        String tempQ1M = Crono.getTimeString();
        Crono.start();
        Map<Integer,Map.Entry<String,Integer>> qT1M = m1.Querie6Test(5);
        String tempQT1M = Crono.getTimeString();
        System.out.println(" ------------------ Testes Querie 6  ------------------\n");
        System.out.println("Original                                 Alterado");
        System.out.println(tempQ1M+"               "+tempQT1M);
    }

    public void querie7Test(Model m1){
        Crono.start();
        Map<Integer,List<String>> q1M = m1.Querie7();
        String tempQ1M = Crono.getTimeString();
        Crono.start();
        Map<Integer,Vector<String>>  qT1M = m1.Querie7Test();
        String tempQT1M = Crono.getTimeString();
        System.out.println(" ------------------ Testes Querie 7  ------------------\n");
        System.out.println("Original                                  Alterado");
        System.out.println(tempQ1M+"               "+tempQT1M);
    }

    public void querie8Test(Model m1){
        Crono.start();
        Map<Integer,Map.Entry<String,Integer>> qT1M = m1.Querie8Test(5);
        String tempQT1M = Crono.getTimeString();
        System.out.println(" ------------------ Testes Querie 8  ------------------\n");
        System.out.println("Original                                  Alterado");
        System.out.println(tempQT1M+"               "+tempQT1M);
    }

    public void querie9Test(Model m1){
        Crono.start();
        Map<Integer,Map.Entry<String,Double>> q1M = m1.Querie9("KR1583",5);
        String tempQ1M = Crono.getTimeString();
        Crono.start();
        Map<Integer,Map.Entry<String,Double>> qT1M = m1.Querie9Test("KR1583",5);
        String tempQT1M = Crono.getTimeString();
        System.out.println(" ------------------ Testes Querie 9  ------------------\n");
        System.out.println("Original                                 Alterado");
        System.out.println(tempQ1M+"               "+tempQT1M);
    }

}
