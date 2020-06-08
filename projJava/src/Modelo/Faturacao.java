package Modelo;

import java.io.Serializable;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;

/**
 * Classe que contém a implementação da Faturação
 */
public class Faturacao implements Serializable {
    private Map<String,Fatura> fat;


    /**
     * Construtor vazio
     */
    public Faturacao(){
        fat = new HashMap<>();
    }

    /**
     * Construtor parametrizado
     * @param fat
     */
    public Faturacao(Map<String, Fatura> fat) {
        this.fat = fat;
    }

    /**
     * Construtor por cópia
     * @param f
     */
    public Faturacao(Faturacao f){
        setFat(f.getFat());
    }


    /**
     * Devolve a faturação
     * @return Map<String, Fatura>
     */
    public Map<String, Fatura> getFat() {
        HashMap<String,Fatura> aux = new HashMap<>();
        for(Map.Entry<String,Fatura> s: this.fat.entrySet()){
            aux.put(s.getKey(),s.getValue().clone());
        }
        return aux;
    }

    /**
     * Define a faturação
     * @param fat
     */
    public void setFat(Map<String, Fatura> fat) {
        this.fat = new HashMap<>();
        for(Map.Entry<String,Fatura> s: fat.entrySet()){
            this.fat.put(s.getKey(),s.getValue().clone());
        }
    }


    /**
     * Devolve uma cópia da instância
     * @return
     */
    public Faturacao clone(){
        return new Faturacao();
    }

    /**
     * Verifica a igualdade com outro objeto
     * @param o          Objeto a comparar
     * @return boolean
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Faturacao)) return false;
        Faturacao faturacao = (Faturacao) o;
        return Objects.equals(getFat(), faturacao.getFat());
    }

    /**
     * Método hashCode do objeto
     * @return hash do objeto
     */
    public int hashCode() {
        return Objects.hash(getFat());
    }

    /**
     * Método toString do objeto
     * @return Objeto em modo string
     */
    public String toString() {
        final StringBuilder sb = new StringBuilder("Faturacao{");
        sb.append("fat=").append(fat);
        sb.append('}');
        return sb.toString();
    }


    /**
     * Função que insere faturação
     * @param venda         Lista de vendas
     */
    public void insereFaturacaoMap(List<Venda> venda){
        for(Venda v: venda){
            String prod = v.getProduto();
            if(this.fat.containsKey(prod)){
                this.fat.get(prod).insereFatura(v);
            }
            else{
                Fatura f = new Fatura();
                f.insereFatura(v);
                this.fat.put(prod,f);
            }
        }
    }


    /**
     * Função que devolve a faturação total, tendo em conta um mês e uma filial
     * @param mes
     * @param filial
     * @return
     */
    public double faturacaoTotal(int mes, int filial){
        double total = 0;
        for(Fatura f: this.getFat().values()){
            total += f.getFaturacao(filial,mes,0) + f.getFaturacao(filial,mes,1);
        }
        return total;
    }

    /**
     * Função que devolve a faturção total, tendo em conta um mês, uma filial e um produto
     * @param mes
     * @param filial
     * @param prod
     * @return
     */
    public double faturacaoTotal(int mes, int filial,String prod){
        double total = 0;
        if(this.getFat().containsKey(prod)){
            Fatura f =this.getFat().get(prod);
            total = f.getFaturacao(filial,mes,0)+f.getFaturacao(filial,mes,1);
        }
        return total;
    }


    /**
     * Função que devolve o número de vendas total, tendo em conta um mês e uma filial
     * @param mes
     * @param filial
     * @return
     */
    public int numVendasTotal(int mes, int filial){
        int num=0;
        for(Fatura f: this.getFat().values()){
            num += f.getNumVendas(filial,mes,0)+f.getNumVendas(filial,mes,1);
        }
        return num;
    }


    /**
     * Função que nos diz se um determinado produto está presente na faturação
     * @param prod
     * @return boolean que dá true se estiver presente e false caso contrário
     */
    public boolean contemProduto(String prod){
        return this.fat.containsKey(prod);
    }

}
