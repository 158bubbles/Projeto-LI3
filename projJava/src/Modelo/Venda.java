package Modelo;

import java.io.Serializable;
import java.util.*;

import static java.lang.Character.isDigit;

/**
 * Classe que contém a implementação da Venda
 */
public class Venda implements Serializable {

    private String produto;
    private double preco;
    private int quantidade;
    private int promocao;
    private String cliente;
    private int mes;
    private int filial;

    /**
     * Construtor vazio
     */
    public Venda(){
        produto = new String();
        preco = 0;
        quantidade = 0;
        promocao = 0;
        cliente = new String();
        mes = 0;
        filial = 0;
    }

    /**
     * Construtor Parametrizado
     * @param produto
     * @param preco
     * @param quantidade
     * @param promocao
     * @param cliente
     * @param mes
     * @param filial
     */
    public Venda(String produto, double preco, int quantidade, int promocao, String cliente, int mes, int filial) {
        this.produto = produto;
        this.preco = preco;
        this.quantidade = quantidade;
        this.promocao = promocao;
        this.cliente = cliente;
        this.mes = mes;
        this.filial = filial;
    }

    /**
     * Construtor por cópia
     * @param v
     */
    public Venda(Venda v){
        this.produto = v.getProduto();
        this.preco = v.getPreco();
        this.quantidade = v.getQuantidade();
        this.promocao = v.getPromocao();
        this.cliente = v.getCliente();
        this.mes = v.getMes();
        this.filial = v.getFilial();
    }

    /**
     * Devolve o código do produto
     * @return string
     */
    public String getProduto() {
        return produto;
    }

    /**
     * Devolve o preço do produto
     * @return double
     */
    public double getPreco() {
        return preco;
    }


    /**
     * Devolve a quantidade do produto
     * @return int
     */
    public int getQuantidade() {
        return quantidade;
    }


    /**
     * Devolve a promoção do produto
     * @return int
     */
    public int getPromocao() {
        return promocao;
    }


    /**
     * Devolve o código do cliente
     * @return string
     */
    public String getCliente() {
        return cliente;
    }


    /**
     * Devolve o mês
     * @return int
     */
    public int getMes() {
        return mes;
    }


    /**
     * Devolve a filial
     * @return int
     */
    public int getFilial() {
        return filial;
    }

    /**
     * Devove a faturação
     * @return double
     */
    public double getFaturacao(){
        return this.preco*this.quantidade;
    }

    /**
     * @return Devolve uma cópia da instância
     */
    public Venda clone(){
        return new Venda(this);
    }

    /**
     * Verifica a igualdade com outro objeto
     * @param o
     * @return boolean
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Venda)) return false;
        Venda venda = (Venda) o;
        return Double.compare(venda.getPreco(), getPreco()) == 0 &&
                getQuantidade() == venda.getQuantidade() &&
                getPromocao() == venda.getPromocao() &&
                getMes() == venda.getMes() &&
                getFilial() == venda.getFilial() &&
                Objects.equals(getProduto(), venda.getProduto()) &&
                Objects.equals(getCliente(), venda.getCliente());
    }

    /**
     * Método hashCode do objeto
     * @return hash do objeto
     */
    public int hashCode() {
        return Objects.hash(getProduto(), getPreco(), getQuantidade(), getPromocao(), getCliente(), getMes(), getFilial());
    }

    /**
     * Método toString do objeto
     * @return Objeto em modo string
     */
    public String toString() {
        final StringBuilder sb = new StringBuilder("Venda{");
        sb.append("produto='").append(produto).append('\'');
        sb.append(", preco=").append(preco);
        sb.append(", quantidade=").append(quantidade);
        sb.append(", promocao=").append(promocao);
        sb.append(", cliente='").append(cliente).append('\'');
        sb.append(", mes=").append(mes);
        sb.append(", filial=").append(filial);
        sb.append('}');
        return sb.toString();
    }

    /**
     * Determina se o produto é válido (está na lista dos produtos válidos)
     * @param produto
     * @param prod
     * @return boolean
     */
    public boolean product(String produto, Set<String> prod){
        return (prod.contains(produto));
    }

    /**
     * Determina se o preço é valido (maior que zero)
     * @param preco
     * @return boolean
     */
    public boolean price(double preco){
        return preco >= 0;
    }

    /**
     * Determina se a quantidade é valida (maior que zero)
     * @param quant
     * @return boolean
     */
    public boolean quantity(int quant){
        return quant >= 0;
    }

    /**
     * Verifica se a promoção é válida (0 ou 1)
     * @param prom
     * @return boolean
     */
    public boolean promotion(int prom){
        return prom == 1 || prom == 0;
    }

    /**
     * Determina se o cliente é válido (está na lista dos clientes válidos)
     * @param cliente
     * @param cli
     * @return
     */
    public boolean client (String cliente,Set<String> cli){
        return (cli.contains(cliente));
    }

    /**
     * Determina se o mês é válido (entre 1 e 12)
     * @param mes
     * @return boolean
     */
    public boolean month (int mes){
        return mes >= 1 && mes <= 12;
    }

    /**
     * Determina se a filial é válida (1, 2 e 3)
     * @param filial
     * @return boolean
     */
    public boolean market(int filial){
        return filial == 1 || filial == 2 || filial == 3;
    }

    /**
     * reúne todos os métodos anteriores, se todos forem True, a venda é dada como válida
     * @param produto
     * @param preco
     * @param quantidade
     * @param promocao
     * @param cliente
     * @param mes
     * @param filial
     * @param prod
     * @param cli
     * @return boolean
     */
    public boolean validVenda(String produto, double preco, int quantidade,
                              int promocao, String cliente, int mes, int filial, Set<String> prod,Set<String> cli){
        return product(produto, prod) && price(preco)
                && quantity(quantidade) && promotion(promocao)
                && client(cliente, cli) && month(mes)
                && market(filial);
    }

    /**
     * Método para comparar a quantidade de produto por ordem decrescente
     * @param v
     * @return int
     */
    public int compareQuant(Venda v){
        if(this.quantidade == v.getQuantidade()){
            if(this.produto.equals(v.getProduto())) return 0;
            if(this.produto.compareTo(v.getProduto()) > 0)
                return 1;
            else return -1;
        }
        if(this.quantidade - v.getQuantidade() > 0) return -1;
        return 1;
    }


}


