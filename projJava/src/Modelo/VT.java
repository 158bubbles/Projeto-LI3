package Modelo;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Classe que contém a implementação da VT
 */
public class VT implements Serializable {
    private List<Venda> vendasVT;
    private int invalidas;

    /**
     * Construtor vazio
     */
    public VT() {
        vendasVT = new ArrayList<>();
        invalidas = 0;
    }

    /**
     * Construtor parametrizado
     * @param vendasVT
     * @param path
     * @param invalidas
     */
    public VT(List<Venda> vendasVT, String path, int invalidas) {
        setVendasVT(vendasVT);
        this.invalidas = invalidas;
    }

    /**
     * Construtor por cópia
     * @param vendas
     */
    public VT(VT vendas) {
        setVendasVT(vendas.getVendasVT());
        this.invalidas = vendas.getInvalidas();
    }

    /**
     * Devolve o número de vendas inválidas
     * @return int
     */
    public int getInvalidas() {
        return invalidas;
    }

    /**
     * Define o número de vendas inválidas
     * @return int
     */
    public void setInvalidas(int invalidas) {
        this.invalidas = invalidas;
    }

    /**
     * Devolve as vendas
     * @return List<Venda>
     */
    public List<Venda> getVendasVT() {
        ArrayList<Venda> aux = new ArrayList<>();
        for (Venda v : this.vendasVT) {
            aux.add(v.clone());
        }
        return aux;
    }

    /**
     * Define as vendas
     * @return
     */
    public void setVendasVT(List<Venda> vendasVT) {
        this.vendasVT = new ArrayList<>();
        for (Venda v : vendasVT) {
            this.vendasVT.add(v.clone());
        }
    }

    /**
     * @return Devolve uma cópia da instância
     */
    public VT clone() {
        return new VT(this);
    }


    /**
     * Verifica a igualdade com outro objeto
     * @param o
     * @return boolean
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof VT)) return false;
        VT vt = (VT) o;
        return Objects.equals(getVendasVT(), vt.getVendasVT());
    }

    /**
     * Método hashCode do objeto
     * @return hash do objeto
     */
    public int hashCode() {
        return Objects.hash(getVendasVT());
    }

    /**
     * Método toString do objeto
     * @return Objeto em modo string
     */
    public String toString() {
        final StringBuilder sb = new StringBuilder("VT{");
        sb.append("vendasVT=").append(vendasVT);
        sb.append('}');
        return sb.toString();
    }

    /**
     * Lê o ficheiro, cria as vendas e adiciona estas ao map vendasVT
     * @param vt
     * @param produtos
     * @param clientes
     * @param path
     * @throws IOException
     */
    public void read_Vendas(VT vt, Set<String> produtos,Set<String> clientes, String path) throws IOException{
        int j=0;
        try{
            FileInputStream stream = new FileInputStream(path);
            InputStreamReader reader = new InputStreamReader(stream);
            BufferedReader br = new BufferedReader(reader);
            String linha = br.readLine();
            while (linha != null) {
                String[] val = linha.split(" ");
                String prod = val[0];
                double preco = Double.parseDouble(val[1]);
                int quant = Integer.parseInt(val[2]);
                char prom = val[3].charAt(0);
                int promocao = 1;
                if (prom == 'N')
                    promocao = 0;
                String cli = val[4];
                int mes = Integer.parseInt(val[5]);
                String[] fil = val[6].split("\r\n");
                int filial = Integer.parseInt(fil[0]);
                Venda v = new Venda(prod, preco, quant, promocao, cli, mes, filial);
                if (v.validVenda(prod, preco, quant, promocao, cli, mes, filial, produtos, clientes)) {
                    this.vendasVT.add(v);
                } else j++;
                linha = br.readLine();
            }
        }
        catch (FileNotFoundException f){
            System.out.println("Ficheiro Venda Inexistente!");
        }
        setInvalidas(j);
    }

    /**
     * Função que obtém o número de clientes distintos
     * @param mes          Mês desejado
     * @param filial       Filial desejado
     * @return int -> número distintos de clientes
     */
    public int clientesDistinct(int mes, int filial){
        return this.vendasVT.stream().filter(a -> a.getMes() == mes && a.getFilial() == filial)
                            .map(Venda::getCliente).distinct().collect(Collectors.toList()).size();
    }

    /**
     * Função que devolve o número de vendas
     * @param mes          Mês desejado
     * @return int -> Retorna o número de compras feitas num determinado mês
     */
    public int numVendas(int mes){
        return (int) this.vendasVT.stream().filter(a->a.getMes() == mes).map(a->a.getProduto()).count();
    }

    /**
     * Função que calcula a faturação total num determinado mês e numa determinada filial
     * @param mes          Mês desejado
     * @param filial       Filial desejada
     * @return double -> faturação total
     */
    public double faturacaoVendas(int mes, int filial){
        double preco =  this.vendasVT.stream().filter(a ->a.getMes() == mes && a.getFilial() == filial)
                                     .mapToDouble(a->a.getPreco()).sum();
        int quant = this.vendasVT.stream().filter(a->a.getMes() == mes && a.getFilial() == filial)
                                     .mapToInt(a->a.getQuantidade()).sum();
        return preco*quant;
    }

    public  Map.Entry<String,String> vendasSemParsing(String path) throws IOException{
        try {
            Crono.start();
            FileInputStream stream = new FileInputStream(path);
            String tempFile = Crono.getTimeString();
            InputStreamReader reader = new InputStreamReader(stream);
            Crono.start();
            BufferedReader br = new BufferedReader(reader);
            String tempBuffer = Crono.getTimeString();
            return new AbstractMap.SimpleEntry<>(tempFile,tempBuffer);
        }
        catch (FileNotFoundException f){
            System.out.println("Ficheiro Venda Inexistente!");
            return null;
        }
    }

    public String vendasComParsing(String path) throws IOException{
        try{
            Crono.start();
            FileInputStream stream = new FileInputStream(path);
            InputStreamReader reader = new InputStreamReader(stream);
            BufferedReader br = new BufferedReader(reader);
            String linha = br.readLine();
            while (linha != null) {
                String[] val = linha.split(" ");
                String prod = val[0];
                double preco = Double.parseDouble(val[1]);
                int quant = Integer.parseInt(val[2]);
                char prom = val[3].charAt(0);
                int promocao = 1;
                if (prom == 'N')
                    promocao = 0;
                String cli = val[4];
                int mes = Integer.parseInt(val[5]);
                String[] fil = val[6].split("\r\n");
                int filial = Integer.parseInt(fil[0]);
                Venda v = new Venda(prod, preco, quant, promocao, cli, mes, filial);
                linha = br.readLine();
            }
            return Crono.getTimeString();
        }
        catch (FileNotFoundException f){
            System.out.println("Ficheiro Venda Inexistente!");
            return null;
        }
    }

    public String vendasComParsingValidacao(VT vt, Set<String> produtos,Set<String> clientes, String path) throws IOException{
        Crono.start();
        int j=0;
        try{
            FileInputStream stream = new FileInputStream(path);
            InputStreamReader reader = new InputStreamReader(stream);
            BufferedReader br = new BufferedReader(reader);
            String linha = br.readLine();
            while (linha != null) {
                String[] val = linha.split(" ");
                String prod = val[0];
                double preco = Double.parseDouble(val[1]);
                int quant = Integer.parseInt(val[2]);
                char prom = val[3].charAt(0);
                int promocao = 1;
                if (prom == 'N')
                    promocao = 0;
                String cli = val[4];
                int mes = Integer.parseInt(val[5]);
                String[] fil = val[6].split("\r\n");
                int filial = Integer.parseInt(fil[0]);
                Venda v = new Venda(prod, preco, quant, promocao, cli, mes, filial);
                if (v.validVenda(prod, preco, quant, promocao, cli, mes, filial, produtos, clientes)) {
                    this.vendasVT.add(v);
                } else j++;
                linha = br.readLine();
            }
        }
        catch (FileNotFoundException f){
            System.out.println("Ficheiro Venda Inexistente!");
        }
        setInvalidas(j);
        return Crono.getTimeString();
    }
}