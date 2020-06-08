import Controller.Controller;
import Modelo.Model;
import View.View;

import java.io.IOException;

public class GestVendasAppMVC {

    public static void main(String[] args) throws ClassNotFoundException, IOException{

        Controller c = new Controller();
        View v = new View();
        Model m = new Model();
        c.interpretador(v,m);



        /*GestVendas sgv = new GestVendas();
        String pathP = "DadosIniciais/Produtos.txt";
        String pathC = "DadosIniciais/Clientes.txt";
        String pathV = "DadosIniciais/Vendas_1M.txt";

        sgv.loadSGV(pathP,pathC,pathV);
        Set<String> q1 = sgv.Querie1();
        System.out.println(q1.size());
        Map<Integer,Map.Entry<Integer,Integer>> q2 = sgv.Querie2(1);
        System.out.println(q2.get(1));
        for(int i = 1; i <= 12; i++) {
            Map.Entry<Integer, Map.Entry<Integer, Double>> q3 = sgv.Querie3("L4891", i);
            if(q3 != null) System.out.println(q3.getValue());
        }
        for(int i = 1; i <= 12; i++) {
            Map.Entry<Integer, Map.Entry<Integer, Double>> q4 = sgv.Querie4("KR1583", i);
            if(q4 != null) System.out.println(i + ": " +q4.getValue());
        }
        List<String> q5 = sgv.Querie5("L4891");
        System.out.println(q5);
        List<String> q6 = sgv.Querie6(5);
        System.out.println(q6);
        Map<Integer,List<String>> q7 = sgv.Querie7();
        System.out.println(q7.get(0));
        List<String> q8 = sgv.Querie8(5);
        System.out.println(q8);
        Map.Entry<List<String>,List<Double>> q9 = sgv.Querie9("KR1583",5);
        System.out.println(q9.getKey());
        Map<Integer,Map<Integer,Double>> q10 = sgv.Querie10();
        for(int i = 1; i <= 12; i++)
            System.out.println(i + ": " +q10.get(i));*/
        //System.out.println(crono.getTimeString());
    }
}
