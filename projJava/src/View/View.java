package View;

import Modelo.Crono;
import Modelo.Fatura;
import Modelo.Model;

import java.io.Serializable;
import java.util.*;

public class View implements Serializable {
    /**
     * Imprime o tempo de duração das funções
     * @param s
     */
    public void tempo(String s){
        System.out.println(s);
    }

    /**
     * Imprime o menu
     */
    public void menu(){
        StringBuilder s = new StringBuilder();
        s.append("--------------- M E N U ---------------\n");
        s.append(" 0 - Iniciar estrutura\n");
        s.append(" 1 - Consultas Interativas \n");
        s.append(" 2 - Consultas Estatísticas \n");
        s.append(" 3 - Guardar estrutura em ficheiro \n");
        s.append(" 4 - Ler estrutura em ficheiro \n");
        s.append(" 5 - Exit \n");
        s.append("Insira um comando :\n");
        System.out.println(s.toString());
    }

    /**
     * Imprime as opçoes de inicialização de estruturas
     */
    public void estrutura(){
        System.out.print("1 - Default\n");
        System.out.print("2 - Manual\n");
    }

    /**
     * Imprime o menu das queries interativas
     */
    public void interativas(){
        StringBuilder s = new StringBuilder();
        s.append("--------------- I N T E R A T I V A S ---------------\n");
        s.append(" 1 - Querie 1 \n");
        s.append(" 2 - Querie 2 \n");
        s.append(" 3 - Querie 3 \n");
        s.append(" 4 - Querie 4 \n");
        s.append(" 5 - Querie 5 \n");
        s.append(" 6 - Querie 6 \n");
        s.append(" 7 - Querie 7 \n");
        s.append(" 8 - Querie 8 \n");
        s.append(" 9 - Querie 9 \n");
        s.append(" 10 - Querie 10 \n");
        s.append(" 11 - Back \n");
        s.append("Insira um comando :\n");
        System.out.println(s.toString());
    }

    /**
     * Imprime o menu das queries estatísticas
     */
    public void estatisticas(){
        StringBuilder s = new StringBuilder();
        s.append("--------------- E S T A T I S T I C A S ---------------\n");
        s.append(" 1 - Consulta 1 \n");
        s.append(" 2 - Consulta 2 \n");
        s.append(" 3 - Back \n");
        s.append("Insira um comando :\n");
        System.out.println(s.toString());
    }

    /**
     * Imprime/adiciona as diretorias para a inicialização das estruturas
     * @return
     */
    public List<String> inicializacao(){
        List<String> aux = new ArrayList<>();
        Scanner sc = new Scanner(System.in);
        int d = sc.nextInt();
        if(d == 1){
            aux.add("DadosIniciais/Produtos.txt");
            aux.add("DadosIniciais/Clientes.txt");
            aux.add("DadosIniciais/Vendas_1M.txt");
        }
        else if(d == 2){
            System.out.print("Insira a diretoria dos produtos: \n");
            aux.add(sc.next());
            System.out.print("Insira a diretoria dos clientes: \n");
            aux.add(sc.next());
            System.out.print("Insira a diretoria das vendas: \n");
            aux.add(sc.next());
        }
        return aux;
    }

    /**
     * Imprime o aviso caso o utilizador nao tenha inicializado nenhuma estrutura
     */
    public void naoInicializada(){
        System.out.println("Estrutura nao inicializada!");
    }


    public String nomeFicheiroBinario(){
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira o nome do ficheiro: \n");
        return sc.next();
    }

    public void erroGravar(){
        StringBuilder s = new StringBuilder();
        s.append("Erro a gravar!");
        System.out.println(s.toString());
    }

    public void  erroLer(){
        StringBuilder s = new StringBuilder();
        s.append("Erro a Ler!");
        System.out.println(s.toString());
    }

    /**
     * Imprime a querie 1
     * @param sgv
     */
    public void printQuerie1(Model sgv) {
        Crono.start();
        List<String> querie1 =  sgv.Querie1();
        String temp  = Crono.getTimeString();

        StringBuilder s = new StringBuilder();
        s.append("--------------------------------------------------------------- Produtos nunca compados --------------------------------------------------------------- \n");
        s.append("\n");
        System.out.print(s.toString());
        int m = 0;
        if (querie1.size() % 10 != 0) {
            StringBuilder d = new StringBuilder();
            int a = 0;
            for (int j = 0; j < (querie1.size() / 10) + 1 && a < querie1.size(); j++) {
                d.append("\n");
                for (int i = 0; i < 10 && m < querie1.size(); i++) {
                    d.append("| ");
                    d.append(m+1);
                    d.append(": ");
                    d.append(querie1.get(a));
                    d.append("\t");
                    m++;
                    a++;
                }
                d.append("|");
            }
            System.out.println(d.toString());
        } else {
            StringBuilder d = new StringBuilder();
            int b = 0;
            for (int j = 0; j < (querie1.size() / 10) && b < querie1.size(); j++) {
                System.out.println();
                for (int i = 0; i < 10 && m < querie1.size(); i++) {
                    d.append("| ");
                    d.append(m+1);
                    d.append(": ");
                    d.append(querie1.get(b));
                    d.append("\t");
                    m++;
                    b++;
                }
                d.append("|");
            }
            System.out.println(d.toString());
        }
        StringBuilder b = new StringBuilder();
        b.append("\n");
        b.append("Numero de produtos nunca comprados: ");
        b.append(querie1.size());
        System.out.println(b.toString());
        System.out.println();
        System.out.println(temp);
    }

    /**
     * Imprime Querie 2
     * @param sgv
     */
    public void printQuerie2(Model sgv) {
        StringBuilder s = new StringBuilder();
        s.append("Escolha a filial: \n");
        s.append("0 - Todas as  filiais\n");
        s.append("1 - Filial 1 \n");
        s.append("2 - Filial 2 \n");
        s.append("3 - Filial 3 \n");
        System.out.print(s.toString());
        Scanner sc = new Scanner(System.in);
        int flag = sc.nextInt();
        StringBuilder m = new StringBuilder();
        m.append("Insira um mes: ");
        System.out.print(m.toString());
        int mes = sc.nextInt();

        Crono.start();
        Map.Entry<Integer, Integer> querie2 = sgv.Querie2(mes, flag);
        String temp = Crono.getTimeString();
        if (flag == 0){
            StringBuilder d = new StringBuilder();
            d.append("Todas as filiais: ");
            d.append("Numero Clientes: ");
            d.append(querie2.getKey());
            d.append("\tNumero de Vendas: ");
            d.append(querie2.getValue());
            System.out.println(d.toString());
        }
        else{
            StringBuilder d = new StringBuilder();
            d.append("Filial ");
            d.append(flag);
            d.append(": ");
            d.append("Numero Clientes: ");
            d.append(querie2.getKey());
            d.append("\tNumero de Vendas: ");
            d.append(querie2.getValue());
            System.out.println(d.toString());
        }
        System.out.println();
        System.out.println(temp);
    }

    /**
     * Corresponde o número do mês a uma String
     * @param mes
     * @return
     */
    public String mes (int mes){
        if(mes == 1) return "Janeiro";
        if(mes == 2) return "Fevereiro";
        if(mes == 3) return "Marco";
        if(mes == 4) return "Abril";
        if(mes == 5) return "Maio";
        if(mes == 6) return "Junho";
        if(mes == 7) return "Julho";
        if(mes == 8) return "Agosto";
        if(mes == 9) return "Setembro";
        if(mes == 10) return "Outubro";
        if(mes == 11) return "Novembro";
        return "Dezembro";
    }

    /**
     * Imprime a Querie 3
     * @param sgv
     */
    public void printQuerie3(Model sgv){
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira um cliente: ");
        String cliente = sc.next();
        int i = 1;
        Crono.start();
        Map<Integer,Map.Entry<Integer, Map.Entry<Integer, Double>>> querie3 = sgv.Querie3(cliente);
        String temp = Crono.getTimeString();

        for(Map.Entry<Integer,Map.Entry<Integer,Double>> aux: querie3.values()){
            StringBuilder s = new StringBuilder();
            String mes = mes(i);
            s.append(mes);
            s.append(": \n");
            Map.Entry<Integer,Double> nova = aux.getValue();
            s.append("Numero de compras: ");
            s.append(aux.getKey());
            s.append("\t");
            s.append("Numero de produtos: ");
            s.append(nova.getKey());
            s.append("\t");
            s.append("Despesa: ");
            s.append(nova.getValue());
            System.out.println(s.toString());
            i++;
        }
        System.out.println();
        System.out.println(temp);
    }

    /**
     * Imprime a Querie 4
     * @param sgv
     */
    public void printQuerie4(Model sgv){
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira um produto: ");
        String produto = sc.next();
        int i = 1;
        Crono.start();
        Map<Integer,Map.Entry<Integer, Map.Entry<Integer, Double>>> querie4 = sgv.Querie4(produto);
        String temp = Crono.getTimeString();
        for(Map.Entry<Integer,Map.Entry<Integer,Double>> sec: querie4.values()){
            StringBuilder s = new StringBuilder();
            String mes = mes(i);
            s.append(mes + ": \n");
            Map.Entry<Integer, Double> aux = sec.getValue();
            s.append("Numero de compras do produto: ");
            s.append(sec.getKey());
            s.append("\t|\t");
            s.append("Numero de clientes que compraram: ");
            s.append(aux.getKey());
            s.append("\t|\t");
            s.append("Faturacao: ");
            s.append(aux.getValue());
            System.out.print(s.toString());
            System.out.println();
            i++;
        }
        System.out.println();
        System.out.println(temp);
    }

    /**
     * Imprime a Querie 5
     * @param sgv
     */
    public void printQuerie5(Model sgv){
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira um cliente: ");
        String cliente = sc.next();
        Crono.start();
        List<String> querie5 = sgv.Querie5(cliente);
        String temp = Crono.getTimeString();
        int m = 0;
        if (querie5.size() % 10 != 0) {
            int a = 0;
            for (int j = 0; j < (querie5.size() / 10) + 1 && a < querie5.size(); j++) {
                System.out.println();
                for (int i = 0; i < 10 && m < querie5.size(); i++) {
                    StringBuilder s = new StringBuilder();
                    s.append("| ");
                    s.append(m+1);
                    s.append(": ");
                    s.append(querie5.get(a));
                    s.append("\t");
                    m++;
                    a++;
                    System.out.println(s.toString());
                }
                System.out.print("|");
            }
        } else {
            int b = 0;
            for (int j = 0; j < (querie5.size() / 10) && b < querie5.size(); j++) {
                System.out.println();
                for (int i = 0; i < 10 && m < querie5.size(); i++) {
                    StringBuilder s = new StringBuilder();
                    s.append("| ");
                    s.append(m + 1);
                    s.append(": ");
                    s.append(querie5.get(b));
                    s.append("\t");
                    m++;
                    b++;
                    System.out.print(s.toString());
                }
                System.out.print("|");
            }
        }
        System.out.println();
        StringBuilder d = new StringBuilder();
        d.append("Numero de produtos comprados por ");
        d.append(cliente);
        d.append(": ");
        d.append(querie5.size());
        System.out.println(d.toString());
        System.out.println();
        System.out.println(temp);
    }

    /**
     * Imprime a Querie 6
     * @param sgv
     */
    public void printQuerie6(Model sgv){
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira o limite: ");
        int limit = sc.nextInt();
        Crono.start();
        Map<Integer,Map.Entry<String,Integer>> querie6 = sgv.Querie6(limit);
        String temp = Crono.getTimeString();
        StringBuilder s = new StringBuilder();
        s.append("------------- Top ");
        s.append(limit);
        s.append(" de produtos mais vendidos ------------- \n");
        System.out.println(s.toString());
        int i = 0;
        for(Map.Entry<String,Integer> sec: querie6.values()){
            System.out.print((i+1) + ": ");
            System.out.print(sec.getKey());
            System.out.print(" -> ");
            System.out.println(sec.getValue());
            i++;
        }
        System.out.println();
        System.out.println(temp);
    }

    /**
     * Imprime a Querie 7
     * @param sgv
     */
    public void printQuerie7(Model sgv){
        int i = 0;
        Crono.start();
        Map<Integer,List<String>> querie7 = sgv.Querie7();
        String temp = Crono.getTimeString();
        System.out.println("------------- Top 3 de maiores compradores ------------- \n");
        for(List<String> aux: querie7.values()){
            StringBuilder e = new StringBuilder();
            e.append("Filial ");
            e.append(i+1);
            e.append(":");
            System.out.print(e.toString());
            System.out.println(aux);
            i++;
        }
        System.out.println();
        System.out.println(temp);
    }

    /**
     * Imprime a Querie 8
     * @param sgv
     */
    public void printQuerie8(Model sgv){
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira o limite: ");
        int limit = sc.nextInt();

        Crono.start();
        Map<Integer,Map.Entry<String,Integer>> querie8 = sgv.Querie8(limit);
        String temp = Crono.getTimeString();
        System.out.print("------------- Top ");
        System.out.print(limit);
        System.out.println(" de clientes que mais compraram ------------- \n");
        int i = 0;
        for(Map.Entry<String,Integer> sec : querie8.values()){
            System.out.print(i+1);
            System.out.print(": ");
            System.out.print(sec.getKey());
            System.out.print(" -> ");
            System.out.println(sec.getValue());
            i++;
        }
        System.out.println();
        System.out.println(temp);
        System.out.println();
    }

    /**
     * Imprime a Querie 9
     * @param sgv
     */
    public void printQuerie9(Model sgv){
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira o produto: ");
        String prod = sc.next();
        System.out.println("Insira o limite: ");
        int limit = sc.nextInt();
        Crono.start();
        Map<Integer,Map.Entry<String,Double>> querie9 = sgv.Querie9(prod,limit);
        String temp = Crono.getTimeString();
        System.out.print("------------- Top ");
        System.out.print(limit);
        System.out.print("  de clientes  que mais compraram o produto ");
        System.out.print(prod);
        System.out.println(" ------------- \n");
        for(Map.Entry<String,Double> sec: querie9.values()){
            System.out.print("Cliente: ");
            System.out.print(sec.getKey());
            System.out.print(" -> Despesa: ");
            System.out.println(sec.getValue());
        }
        System.out.println();
        System.out.println(temp);
    }

    /**
     * Imprime a Querie 10
     * @param sgv
     */
    public void printQuerie10(Model sgv){
        Crono.start();
        Map<String, Fatura> querie10 = sgv.Querie10();
        String temp = Crono.getTimeString();
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira o produto: ");
        String prod = sc.next();
        //   mes         filial  fat
        Fatura f = querie10.get(prod);
        int mes,filial;
        System.out.print("Produto -> ");
        System.out.println(prod);
        for(mes = 0; mes < 12; mes++){
            System.out.print(mes(mes+1));
            System.out.println(": ");
            for(filial = 0; filial < 3; filial++){
                System.out.print("\t\tFilial ");
                System.out.print(filial+1);
                System.out.print(" -> ");
                double fat = f.getFaturacao(filial,mes,0) + f.getFaturacao(filial,mes,1);
                System.out.println(fat);
            }
        }
        System.out.println();
        System.out.println(temp);
    }

    /**
     * Imprime a consulta estatística 1
     * @param sgv
     */
    public void printconsulta1(Model sgv){
        Crono.start();
        Map.Entry<Integer,Map.Entry<Integer,Integer>> c1 = sgv.estatistica1();
        String temp = Crono.getTimeString();
        System.out.print("Nome do ficheiro                        -> ");
        System.out.println(sgv.getPath());
        System.out.print("Linhas Inválidas                        -> ");
        System.out.println(sgv.getV().getInvalidas());
        System.out.print("Número de produtos                      -> ");
        System.out.println(sgv.getP().getProdutos().size());
        System.out.print("Número de produtos diferentes comprados -> ");
        System.out.println(c1.getKey());
        System.out.print("Número de produtos não comprados        -> ");
        System.out.println(sgv.getP().getProdutos().size()-c1.getKey());
        System.out.print("Número de clientes                      -> ");
        System.out.println(sgv.getC().getClientes().size());
        System.out.print("Número de clientes que compraram        -> ");
        System.out.println(c1.getValue().getKey());
        System.out.print("Número de clientes que não compraram    -> ");
        System.out.println(sgv.getC().getClientes().size()-c1.getValue().getKey());
        System.out.print("Total de compras de valor 0             -> ");
        System.out.println(c1.getValue().getValue());
        double fat = 0;
        for(int i = 0; i < 12; i++) {
            for (int j = 0; j < sgv.getN(); j++)
                fat += sgv.getF().faturacaoTotal(i, j);
        }
        System.out.print("Faturação Total                         -> ");
        System.out.println(fat);
        System.out.println();
        System.out.println(temp);
    }

    /**
     * Imprime a consulta estatística 2
     * @param sgv
     */
    public void printconsulta2(Model sgv){
        Crono.start();
        Map<Integer,Map.Entry<Integer,Map<Integer,Map.Entry<Double,Integer>>>> c2 = sgv.estatistica2();
        String temp = Crono.getTimeString();
        int mes,filial;
        double fatGlobal;
        mes = 1;
        for(Map.Entry<Integer,Map<Integer,Map.Entry<Double,Integer>>> aux: c2.values()) {
            fatGlobal = 0;
            filial = 1;
            System.out.print(mes(mes));
            System.out.print(": \n");
            System.out.print("\t\tNumero de Compras -> ");
            System.out.println(aux.getKey());
            Map<Integer,Map.Entry<Double,Integer>> nova = aux.getValue();
            for (Map.Entry<Double, Integer> b : nova.values()) {
                System.out.print("\t\tFilial ");
                System.out.print(filial);
                System.out.print(": \n");
                System.out.print("\t\t\tFaturação -> ");
                System.out.println(b.getKey());
                fatGlobal += b.getKey();
                System.out.print("\t\t\tClientes Distintos -> ");
                System.out.println(b.getValue());
                System.out.println();
                filial++;
            }
            System.out.print("Faturacao global: ");
            System.out.println(fatGlobal);
            System.out.println();
            mes++;
        }
        System.out.println();
        System.out.println(temp);
    }
}

