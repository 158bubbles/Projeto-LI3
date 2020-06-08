package Modelo;

import java.io.Serializable;
import java.util.Objects;

/**
 * Classe que contém a implementação da estrutura PpC
 */
public class PpC implements Serializable {
    private String produto;
    private double fat;

    /**
     * Construtor vazio
     */
    public PpC(){
        produto = new String();
        fat = 0;
    }

    /**
     * Construtor parametrizado
     * @param produto
     * @param fat
     */
    public PpC(String produto, double fat){
        this.produto = produto;
        this.fat = fat;
    }

    /**
     * Construtor por cópia
     * @param p
     */
    public PpC(PpC p){
        this.produto = p.getProduto();
        this.fat = p.getFat();
    }

    /**
     * Devolve o código do produto
     * @return string
     */
    public String getProduto() {
        return produto;
    }

    /**
     * Define o código do produto
     * @return
     */
    public void setProduto(String produto) {
        this.produto = produto;
    }

    /**
     * Devolve a faturação daquele produto
     * @return double
     */
    public double getFat() {
        return fat;
    }

    /**
     * Verifica a igualdade com outro objeto
     * @param o
     * @return boolean
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof PpC)) return false;
        PpC ppC = (PpC) o;
        return Double.compare(ppC.getFat(), getFat()) == 0 &&
                Objects.equals(getProduto(), ppC.getProduto());
    }

    /**
     * Método hashCode do objeto
     * @return hash do objeto
     */
    public int hashCode() {
        return Objects.hash(getProduto(), getFat());
    }

    /**
     * Método toString do objeto
     * @return Objeto em modo string
     */
    public String toString() {
        final StringBuilder sb = new StringBuilder("PpC{");
        sb.append("produto='").append(produto).append('\'');
        sb.append(", fat=").append(fat);
        sb.append('}');
        return sb.toString();
    }
    /**
     * @return Devolve uma cópia da instância
     */
    public PpC clone(){
        return new PpC(this);
    }

    /**
     * Insere a informação das vendas na variável (faturação)
     * @param v
     */
    public void inserePpC(Venda v){
        setProduto(v.getProduto());
        this.fat += v.getPreco() * v.getQuantidade();
    }

}