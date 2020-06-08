package Modelo;

import java.io.*;
import java.util.*;
import java.lang.Object;
import java.lang.String;

import static java.lang.Character.isDigit;
import static java.lang.Character.isUpperCase;

/**
 * Classe que contém a implementação da estrutura dos Clientes
 */
public class Clientes implements Serializable{
    private Set<String> clientes;


    /**
     * Construtor vazio
     */
    public Clientes() {
        this.clientes = new TreeSet<>();
    }

    /**
     * Construtor parametrizado
     * @param clientes
     */
    public Clientes(Set clientes) {
        this.clientes = clientes;
    }

    /**
     * Construtor por copia
     * @param c
     */
    public Clientes(Clientes c) {
        this.clientes = c.getClientes();
    }


    /**
     * Devolve os clientes
     * @return set<String>
     */
    public Set<String> getClientes() {
        Set<String> aux = new TreeSet<>();
        for (String s : this.clientes) {
            aux.add(s);
        }
        return aux;
    }

    /**
     * Define os clientes
     * @param clientes
     */
    public void setClientes(Set<String> clientes) {
        this.clientes = new TreeSet<>();
        for (String s : clientes) {
            this.clientes.add(s);
        }
    }


    /**
     * Verifica a igualdade com outro objeto
     * @param o          Objeto a comparar
     * @return boolean
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Clientes)) return false;
        Clientes clientes1 = (Clientes) o;
        return Objects.equals(getClientes(), clientes1.getClientes());
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
        final StringBuilder sb = new StringBuilder("Clientes{");
        sb.append("clientes=").append(clientes);
        sb.append('}');
        return sb.toString();
    }


    /**
     * Devolve uma cópia da instância
     * @return
     */
    public Clientes clone() {
        return new Clientes(this);
    }


    /**
     * Função que valida um cliente
     * @param str     String cliente
     * @return boolean que dá true se a string for válida e false se não for
     */
    public boolean valid(String str) {
        int i;
        boolean flag = true;
        int l = str.length();
        if (isUpperCase(str.charAt(0)) && l == 5) {
            for (i = 1; i < l && flag; i++) {
                if (!(isDigit(str.charAt(i))))
                    flag = false;
            }
        } else flag = false;
        return flag;
    }


    /**
     * Função que lê os clientes
     * @param path     Caminho do ficheiro
     * @return Clientes lidos com sucesso
     * @throws FileNotFoundException
     * @throws IOException
     */
    public Set<String> read_Clientes(String path) throws FileNotFoundException,IOException {
        try {
            FileInputStream stream = new FileInputStream(path);
            InputStreamReader reader = new InputStreamReader(stream);
            BufferedReader br = new BufferedReader(reader);
            String linha = br.readLine();
            while (linha != null) {
                String[] val = linha.split("\r\n");
                if (valid(val[0])) {
                    clientes.add(val[0]);
                }
                linha = br.readLine();
            }
        }
        catch (FileNotFoundException f){
            System.out.println("Ficheiro Clientes inexistente!");
        }
        return this.clientes;
    }
}
