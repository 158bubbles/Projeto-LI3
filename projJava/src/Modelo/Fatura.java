package Modelo;

import java.io.Serializable;
import java.util.Arrays;
import java.util.Objects;

/**
 * Classe que contém a implementação da Fatura
 */
public class Fatura implements Serializable {
    private String produto;
    private int[][][] numVendas;
    private double[][][] faturacao;


    /**
     * Construtor vazio
     */
    public Fatura(){
        produto = new String();
        numVendas = new int[3][12][2];
        faturacao = new double[3][12][2];
        int i,j,k;
        for(i = 0; i < 3; i++){
            for(j = 0; j < 12; j++){
                for(k = 0; k < 2; k++){
                    this.numVendas[i][j][k] = 0;
                    this.faturacao[i][j][k] = 0;
                }
            }
        }
    }

    /**
     * Construtor parametrizado
     * @param produto
     * @param numVendas
     * @param faturacao
     */
    public Fatura(String produto, int[][][] numVendas, double[][][] faturacao) {
        this.produto = produto;
        this.numVendas = numVendas;
        this.faturacao = faturacao;
    }

    /**
     * Construtor por cópia
     * @param f
     */
    public Fatura(Fatura f){
        this.produto = f.getProduto();
        this.numVendas = f.getNumVendas();
        this.faturacao =f.getFaturacao();
    }


    /**
     * Devolve um produto
     * @return String
     */
    public String getProduto() {
        return produto;
    }

    /**
     * Define um produto
     * @param produto
     */
    public void setProduto(String produto) {
        this.produto = produto;
    }

    /**
     * Devolve o número de vendas
     * @return int
     */
    public int[][][] getNumVendas() {
        return numVendas;
    }

    /**
     * Define o número de vendas
     * @param numVendas
     */
    public void setNumVendas(int[][][] numVendas) {
        this.numVendas = numVendas;
    }

    /**
     * Devolve a faturação
     * @return double
     */
    public double[][][] getFaturacao() {
        return faturacao;
    }

    /**
     * Define a faturação
     * @param faturacao
     */
    public void setFaturacao(double[][][] faturacao) {
        this.faturacao = faturacao;
    }


    /**
     * Função que obtem o numero de vendas, tendo em conta a filial, o mês e a promoção
     * @param filial
     * @param mes
     * @param prom
     * @return Número de vendas obtido
     */
    public int getNumVendas(int filial, int mes, int prom) {
        return numVendas[filial][mes][prom];
    }

    /**
     * Função que obtem a faturação, tendo em conta a filial, o mês e a promoção
     * @param filial
     * @param mes
     * @param prom
     * @return Faturação obtida
     */
    public double getFaturacao(int filial, int mes, int prom) {
        return faturacao[filial][mes][prom];
    }

    /**
     * Verifica a igualdade com outro objeto
     * @param o
     * @return boolean
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Fatura)) return false;
        Fatura fatura = (Fatura) o;
        return Objects.equals(getProduto(), fatura.getProduto()) &&
                Arrays.equals(getNumVendas(), fatura.getNumVendas()) &&
                Arrays.equals(getFaturacao(), fatura.getFaturacao());
    }

    /**
     * Método hashCode do objeto
     * @return hash do objeto
     */
    public int hashCode() {
        int result = Objects.hash(getProduto());
        result = 31 * result + Arrays.hashCode(getNumVendas());
        result = 31 * result + Arrays.hashCode(getFaturacao());
        return result;
    }

    /**
     * Método toString do objeto
     * @return Objeto em modo string
     */
    public String toString() {
        final StringBuilder sb = new StringBuilder("Fatura{");
        sb.append("produto='").append(produto).append('\'');
        sb.append(", numVendas=").append(Arrays.toString(numVendas));
        sb.append(", faturacao=").append(Arrays.toString(faturacao));
        sb.append('}');
        return sb.toString();
    }

    /**
     * Devolve uma cópia da instância
     * @return
     */
    public Fatura clone(){
        return new Fatura(this);
    }

    /**
     * Função que insere uma fatura
     * @param v       Venda
     */
    public void insereFatura(Venda v){
        this.produto = v.getProduto();
        int filial = v.getFilial();
        int mes = v.getMes();
        int prom = v.getPromocao();
        this.numVendas[filial-1][mes-1][prom]++;
        this.faturacao[filial-1][mes-1][prom] += (v.getPreco())*(v.getQuantidade());
    }


}
