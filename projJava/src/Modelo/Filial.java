package Modelo;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Classe que contém a implementação da estrutura da Filial
 */
public class Filial implements Serializable {
    private Map<String,ClieP> clientes;


    /**
     * Construtor vazio
     */
    public Filial(){
        clientes = new HashMap<>();
    }


    /**
     * Construtor parametrizado
     * @param c
     */
    public Filial(Map<String,ClieP> c){
        setClientes(c);
    }


    /**
     * Construtor por cópia
     * @param f
     */
    public Filial(Filial f){
        setClientes(f.getClientes());
    }


    /**
     * Devolve os clientes
     * @return Map<String, ClieP>
     */
    public Map<String, ClieP> getClientes() {
        HashMap<String,ClieP> aux = new HashMap<>();
        for(Map.Entry<String,ClieP> s: this.clientes.entrySet()){
            aux.put(s.getKey(),s.getValue().clone());
        }
        return aux;
    }


    /**
     * Define os clientes
     * @param clientes
     */
    public void setClientes(Map<String, ClieP> clientes) {
        this.clientes = new HashMap<>();
        for(Map.Entry<String,ClieP> s: clientes.entrySet()){
            this.clientes.put(s.getKey(),s.getValue().clone());
        }
    }

    /**
     * Verifica a igualdade com outro objeto
     * @param o          Objeto a comparar
     * @return boolean
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Filial)) return false;
        Filial filial = (Filial) o;
        return Objects.equals(getClientes(), filial.getClientes());
    }

    /**
     * Método hashCode do objeto
     * @return hash do objeto
     */
    public int hashCode() {
        return Objects.hash(getClientes());
    }

    /**
     * Método toString do objeto
     * @return Objeto em modo string
     */
    public String toString() {
        final StringBuilder sb = new StringBuilder("Filial{");
        sb.append("clientes=").append(clientes);
        sb.append('}');
        return sb.toString();
    }

    /**
     * Devolve uma cópia da instância
     * @return
     */
    public Filial clone(){
        return new Filial(this);
    }


    /**
     * Função que insere uma filial
     * @param v          Venda
     */
    public void insereFilial(Venda v){
        String cli = v.getCliente();
        if(this.clientes.get(cli) != null){
            this.clientes.get(cli).insereClieP(v);
        }
        else{
            ClieP c = new ClieP();
            c.insereClieP(v);
            this.clientes.put(cli,c);
        }
    }


    /**
     * Função de devolve uma lista de produtos
     * @return
     */
    public Map<String, Set<String>> listaProdutos(){
        return this.getClientes().entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, a->a.getValue().getKeyPpC()));
    }


    /**
     * Função que devolve o número de vendas, dado o mês
     * @param mes
     * @return
     */
    public int numVendas(int mes){
        int num = 0;
        for(ClieP p: clientes.values()){
            num += p.getNumVendas(mes);
        }
        return num;
    }
}
