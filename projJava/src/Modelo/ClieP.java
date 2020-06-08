package Modelo;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Classe que contém a implementação da estrutura ClieP
 */
public class ClieP implements Serializable {
    private String cliente;
    private int[] numVendas;
    private Map<String,PpC> p;

    /**
     * Construtor vazio
     */
    public ClieP (){
        cliente = new String();
        numVendas = new int[12];
        for(int i = 0; i < 12; i++){
            numVendas[i] = 0;
        }
        p = new HashMap<>();
    }

    /**
     * Construtor parametrizado
     * @param cliente
     * @param p
     * @param num
     */
    public ClieP(String cliente, Map<String,PpC> p,int[] num){
        this.cliente = cliente;
        this.numVendas = num;
        setP(p);
    }

    /**
     * Construtor por cópia
     * @param p
     */
    public ClieP(ClieP p){
        this.cliente = p.getCliente();
        this.numVendas = p.getNumVendas();
        setP(p.getP());
    }

    /**
     * Devove o código do cliente
     * @return string
     */
    public String getCliente() {
        return cliente;
    }

    /**
     * Devolve o número de vendas
     * @return int
     */
    public int[] getNumVendas() {
        return numVendas;
    }

    /**
     * Devolve o número de vendas num dado mês
     * @return double
     */
    public int getNumVendas(int mes){
        return numVendas[mes];
    }


    /**
     * Devolve o map p
     * @return Map<String,PpC>
     */
    public Map<String,PpC> getP() {
        Map<String,PpC> aux = new HashMap<>();
        for(Map.Entry<String,PpC> p: this.p.entrySet()){
            aux.put(p.getKey(),p.getValue().clone());
        }
        return aux;
    }

    /**
     * Define o map p
     * @return Map<String,PpC>
     */
    public void setP(Map<String,PpC> p) {
        this.p = new HashMap<>();
        for(Map.Entry<String,PpC> ppc: p.entrySet()){
            this.p.put(ppc.getKey(),ppc.getValue().clone());
        }
    }

    /**
     * @return Devolve uma cópia da instância
     */
    public ClieP clone(){
        return new ClieP(this);
    }

    /**
     * Verifica a igualdade com outro objeto
     * @param o
     * @return boolean
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof ClieP)) return false;
        ClieP clieP = (ClieP) o;
        return Objects.equals(getCliente(), clieP.getCliente()) &&
                Arrays.equals(getNumVendas(), clieP.getNumVendas()) &&
                Objects.equals(getP(), clieP.getP());
    }

    /**
     * Método hashCode do objeto
     * @return hash do objeto
     */
    public int hashCode() {
        int result = Objects.hash(getCliente(), getP());
        result = 31 * result + Arrays.hashCode(getNumVendas());
        return result;
    }

    /**
     * Método toString do objeto
     * @return Objeto em modo string
     */
    public String toString() {
        final StringBuilder sb = new StringBuilder("ClieP{");
        sb.append("cliente='").append(cliente).append('\'');
        sb.append(", numVendas=").append(Arrays.toString(numVendas));
        sb.append(", p=").append(p);
        sb.append('}');
        return sb.toString();
    }

    /**
     *
     * @param v
     */
    public void insereClieP(Venda v){
        String prod = v.getProduto();
        if(this.p.containsKey(prod)){
            this.p.get(v.getProduto()).inserePpC(v);
            this.numVendas[v.getMes()-1]++;
            this.cliente = v.getCliente();
        }
        else {
            PpC ppc = new PpC();
            ppc.inserePpC(v);
            this.numVendas[v.getMes()-1]++;
            this.cliente = v.getCliente();
            this.p.put(prod,ppc);
        }
    }

    /**
     * devolve a faturação daquele produto
     * @return
     */
    public double getFaturacaoTotalClieP(){
        double total = 0;
        for(PpC p: this.p.values()){
            total += p.getFat();
        }
        return total;
    }

    /**
     * Método que compara a faturação entre dois produtos por ordem decrescente
     * @param p
     * @return
     */
    public int compareFaturacao(ClieP p){
        if(getFaturacaoTotalClieP() == p.getFaturacaoTotalClieP()) return 0;
        else if( getFaturacaoTotalClieP() - p.getFaturacaoTotalClieP() > 0) return -1;
        return 1;
    }

    /**
     * Devolve um set das keys do map p (códigos de produtos)
     * @return Set<String>
     */
    public Set<String> getKeyPpC(){
        return this.p.entrySet().stream().map(Map.Entry::getKey).collect(Collectors.toSet());
    }


}
