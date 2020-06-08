package Modelo;

import java.io.*;
import java.util.*;
import java.lang.Object;
import java.lang.String;

import static java.lang.Character.isDigit;
import static java.lang.Character.isUpperCase;


/**
 * Classe que contém a implementação dos produtos
 */
public class Produtos implements Serializable  {

    private Set<String> produtos;


    /**
     * Construtor vazio
     */
    public Produtos() {
        this.produtos = new TreeSet<>();
    }

    /**
     * Construtor parametrizado
     * @param produtos
     */
    public Produtos(Set<String> produtos) {
        this.produtos = produtos;
    }

    /**
     * Construtor por cópia
     * @param p
     */
    public Produtos (Produtos p){
        this.produtos = p.getProdutos();
    }


    /**
     * Devolve os produtos
     * @return set<String>
     */
    public Set<String> getProdutos() {
        Set<String> aux = new TreeSet<>();
        for(String s: this.produtos){
            aux.add(s);
        }
        return aux;
    }

    /**
     * Define os produtos
     * @param produtos
     */
    public void setProdutos(ArrayList<String> produtos) {
        this.produtos = new TreeSet<>();
        for (String s : produtos) {
            this.produtos.add(s);
        }
    }


    /**
     * Verifica a igualdade com outro objeto
     * @param o         Objeto a comparar
     * @return boolean
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Produtos)) return false;
        Produtos produtos1 = (Produtos) o;
        return Objects.equals(getProdutos(), produtos1.getProdutos());
    }


    /**
     * Método hashCode do objeto
     * @return hash do objeto
     */
    public int hashCode() {
        return Objects.hash(getProdutos());
    }


    /**
     * Método toString do objeto
     * @return objeto em modo string
     */
    public String toString() {
        final StringBuilder sb = new StringBuilder("Produtos{");
        sb.append("produtos=").append(produtos);
        sb.append('}');
        return sb.toString();
    }


    /**
     * Devolve uma cópia da instância
     * @return
     */
    public Produtos clone(){
        return new Produtos(this);
    }


    /**
     * Função que valida um produto
     * @param str          String produto
     * @return boolean que dá true se a string for válida e false se não for
     */
    public boolean valid(String str) {
        int i;
        boolean flag = true;
        int l = str.length();
        if(isUpperCase(str.charAt(0)) && isUpperCase(str.charAt(1)) && l == 6){
            for(i = 2; i < l && flag; i++){
                if(!(isDigit(str.charAt(i))))
                    flag = false;
            }
        }
        else flag = false;
        return flag;
    }


    /**
     * Função que lê os produtos
     * @param path         Caminho do ficheiro
     * @return Produtos lidos com sucesso
     * @throws FileNotFoundException
     * @throws IOException
     */
    public Set<String> read_Produtos (String path) throws FileNotFoundException,IOException{
        try {
            FileInputStream stream = new FileInputStream(path);
            InputStreamReader reader = new InputStreamReader(stream);
            BufferedReader br = new BufferedReader(reader);
            String linha = br.readLine();
            while (linha != null) {
                String[] val = linha.split("\r\n");
                if (valid(val[0])) {
                    produtos.add(val[0]);
                }
                linha = br.readLine();
            }
        }
        catch (FileNotFoundException f){
            System.out.println("Ficheiro Produtos inexistente");
        }

        return this.produtos;
    }
}
