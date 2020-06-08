package Modelo;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Classe que contém a implementação do Model
 */
public class Model implements Serializable{
    private String path;
    private Produtos p;
    private Clientes c;
    private VT v;
    private Faturacao f;
    private Filial[] filial;
    public static int N = 3;

    /**
     * Construtor vazio
     */
    public Model(){
        path = new String();
        p = new Produtos();
        c = new Clientes();
        v = new VT();
        f = new Faturacao();
        filial = new Filial[N];
        for(int i = 0; i < N; i++){
            filial[i] = new Filial();
        }
    }

    /**
     * Construtor parametrizado
     * @param path
     * @param p
     * @param c
     * @param v
     * @param f
     * @param filial
     */

    public Model(String path, Produtos p, Clientes c, VT v, Faturacao f, Filial[] filial) {
        this.path = path;
        this.p = p;
        this.c = c;
        this.v = v;
        this.f = f;
        this.filial = filial;
    }

    /**
     * Construtor por copia
     * @param gV
     */
    public Model(Model gV){
        this.path = gV.getPath();
        this.p = gV.getP();
        this.c = gV.getC();
        this.v = gV.getV();
        this.f = gV.getF();
        this.filial = gV.getFilial();
    }

    /**
     * Devolve path
     * @return String
     */
    public String getPath() {
        return path;
    }

    /**
     * Define o caminho
     * @param path
     */
    public void setPath(String path) {
        this.path = path;
    }

    /**
     * Devolve Produtos
     * @return Produtos
     */
    public Produtos getP() {
        return p;
    }

    /**
     * Devolve Clientes
     * @return Clientes
     */
    public Clientes getC() {
        return c;
    }

    /**
     * Devolve VT
     * @return VT
     */
    public VT getV() {
        return v;
    }

    /**
     * Devolve Faturacao
     * @return Faturacao
     */
    public Faturacao getF() {
        return f;
    }

    /**
     * Devolve array de Filial
     * @return Filial[]
     */
    public Filial[] getFilial() {
        return filial;
    }

    /**
     * Devolve o N (tamanho do array de Filial -> Filial[])
     * @return int
     */
    public static int getN() {
        return N;
    }

    /**
     * Função que inicializa todas as estruturas a partir dos ficheiros lidos
     * @param pathP       Diretoria dos Produtos
     * @param pathC       Diretoria dos Clientes
     * @param pathV       Diretoria das Vendas
     * @throws IOException
     */
    public void loadSGV(String pathP, String pathC, String pathV) throws IOException {
        path = pathV;
        p.read_Produtos(pathP);
        c.read_Clientes(pathC);
        v.read_Vendas(v,p.getProdutos(),c.getClientes(),pathV);
        f.insereFaturacaoMap(v.getVendasVT());
        for(Venda venda: v.getVendasVT()){
            int j = venda.getFilial();
            this.filial[j-1].insereFilial(venda);
        }
    }

    /**
     * Querie 1 -> Função que devolve uma lista ordenada com codigo de produtos nunca comprados
     * @return List<String> -> Lista ordenada dos produtos.
     */
    public List<String> Querie1(){
        List<String> q1 =  new ArrayList<>();
        for(String prod: p.getProdutos()) {
            if (!this.f.contemProduto(prod)){
                q1.add(prod);
            }
        }
        return q1.stream().sorted().collect(Collectors.toList());
    }

    /**
     * Querie 2 -> Função que determina o número total de vendas realizadas (2º parametro da Map)
     *             e o número total de clientes distintos que as fizeram (1ª parametro da Map)
     * @param mes         Mês valido desejado
     * @param flag        Variavel que indica a filial desejada
     *                              0 -> Todas as filiais
     *                              1 a 3 -> Filial
     * @return Map.Entry<Integer,Integer>
     */
    public Map.Entry<Integer,Integer> Querie2(int mes,int flag){
        int i;
        if(flag == 0){
            int numClientes = 0,numVendas = 0;
            for(i = 0; i < N; i++) {
                List<ClieP> clien = new ArrayList<>(filial[i].getClientes().values());
                numClientes += (int) clien.stream().filter(a -> a.getNumVendas(mes - 1) > 0).count();
                numVendas += clien.stream().filter(a -> a.getNumVendas(mes - 1) > 0).map(a -> a.getNumVendas(mes - 1))
                        .mapToInt(Integer::intValue).sum();
            }
            return new AbstractMap.SimpleEntry<>(numClientes,numVendas);

        }
        else{
            List<ClieP> clien = new ArrayList<>(filial[flag-1].getClientes().values());
            int numClientes = (int) clien.stream().filter(a -> a.getNumVendas(mes - 1) > 0).count();
            int numVendas = clien.stream().filter(a -> a.getNumVendas(mes - 1) > 0).map(a -> a.getNumVendas(mes - 1))
                    .mapToInt(Integer::intValue).sum();
            return new AbstractMap.SimpleEntry<>(numClientes, numVendas);
        }
    }

    /**
     * Querie 3 -> Função que dado um cliente, mês a mês (key) ,
     *             determina o número de compras realizadas (values.key),
     *             determina o número de produtos distintos que comprou (values.values.key)
     *             determina a despesa mensal do cliente (values.values.values)
     * @param cliente       Código do clientes
     * @return Map<Integer,Map.Entry<Integer,Map.Entry<Integer,Double>>> -> Estrutura que contém a informação necessaria para responder à querie 3
     */
    public Map<Integer,Map.Entry<Integer,Map.Entry<Integer,Double>>> Querie3(String cliente){
        //   mes               nCompras        nProdutos  Despesa
        Map<Integer,Map.Entry<Integer,Map.Entry<Integer,Double>>> q3 = new HashMap<>();
        if(!(this.c.valid(cliente))) return null;
        for(int i = 0; i < 12; i++) {
            int finalI = i;
            List<Venda> cli = this.v.getVendasVT().stream().filter(a -> a.getMes() == finalI && a.getCliente().equals(cliente)).collect(Collectors.toList());
            int numP = (int) cli.stream().map(Venda::getProduto).distinct().count();
            double fat = cli.stream().mapToDouble(Venda::getFaturacao).sum();
            q3.put(i, new AbstractMap.SimpleEntry<>(cli.size(), new AbstractMap.SimpleEntry<>(numP, fat)));
        }
        return q3;
    }

    /**
     * Querie 4 -> Função que dado um produto, mês a mês (key) ,
     *             determina o número de vez que foi comprado (values.key),
     *             determina o número de clientes distintos que o compraram (values.values.key)
     *             determina a faturação mensal do produto (values.values.values)
     * @param produto        Código do produto
     * @return Map<Integer,Map.Entry<Integer,Map.Entry<Integer,Double>>> -> Estrutura que contém a informação necessaria para responder à querie 4
     */
    public Map<Integer,Map.Entry<Integer,Map.Entry<Integer,Double>>> Querie4(String produto){
        //  mes               nCompras        nClientes Faturacao
        Map<Integer,Map.Entry<Integer,Map.Entry<Integer,Double>>> q4 = new HashMap<>();
        if(!(this.p.valid(produto))) return null;
        for(int i = 0; i < 12; i++) {
            int mes = i;
            List<Venda> prod = this.v.getVendasVT().stream().filter(a -> a.getMes() == mes && a.getProduto().equals(produto)).collect(Collectors.toList());
            int numC = (int) prod.stream().map(Venda::getCliente).distinct().count();
            double fat = prod.stream().mapToDouble(Venda::getFaturacao).sum();
            q4.put(mes, new AbstractMap.SimpleEntry<>(prod.size(), new AbstractMap.SimpleEntry<>(numC, fat)));
        }
        return q4;
    }

    /**
     * Querie 5 -> Função que dado um cliente, determina a lista de produtos mais comprados
     *             ordenados por ordem decrescente de quantidade, ou alfabeticamente quando quantidade igual.
     * @param cliente        Código do cliente
     * @return List<String> -> Lista de  produtos ordenada
     */
    public List<String> Querie5 (String cliente){
        if(!(this.c.valid(cliente))) return null;
        return this.v.getVendasVT().stream().filter(a->a.getCliente().equals(cliente))
                .sorted(Venda::compareQuant).map(Venda::getProduto)
                .collect(Collectors.toList());
    }

    /**
     * Querie 5 Test -> Função que dado um cliente, determina a lista de produtos mais comprados
     *             ordenados por ordem decrescente de quantidade, ou alfabeticamente quando quantidade igual.
     * @param cliente        Código do cliente
     * @return Vector<String> -> Vetor de  produtos ordenada
     */
    public Vector<String> Querie5Test (String cliente){
        if(!(this.c.valid(cliente))) return null;
        return this.v.getVendasVT().stream().filter(a->a.getCliente().equals(cliente))
                .sorted(Venda::compareQuant).map(Venda::getProduto)
                .collect(Collectors.toCollection(Vector::new));
    }

    /**
     * Querie 6 -> Funcao que determina os X (key)
     *             produtos mais vendidos anualmente (value.key)
     *             número de clientes que o compraram (value.value.key)
     * @param limit           Limite desejado
     * @return Map<Integer,Map.Entry<String,Integer>> -> Estrutura que contem a informação necessária para responder a a querie 6
     */
    public Map<Integer,Map.Entry<String,Integer>> Querie6 (int limit){
        //  limit           produtos nClientes
        Map<Integer,Map.Entry<String,Integer>> q6 = new HashMap<>();
        List<String> produtos = this.v.getVendasVT().stream().collect(Collectors.toMap(Venda::getProduto,Venda::getQuantidade,Integer::sum)).entrySet()
                .stream().sorted((a,b) -> -(a.getValue()-b.getValue())).map(Map.Entry::getKey)
                .limit(limit).collect(Collectors.toList());
        int num;
        List<Integer> clientes = new ArrayList<>();
        for(String s: produtos){
            num = (int) this.v.getVendasVT().stream().filter(a->a.getProduto().equals(s)).map(Venda::getCliente).distinct().count();
            clientes.add(num);
        }
        for(int i = 0; i < limit; i++){
            q6.put(i,new AbstractMap.SimpleEntry<>(produtos.get(i),clientes.get(i)));
        }
        return q6;
    }

    /**
     * Querie 6 Teste -> Funcao que determina os X (key)
     *                   produtos mais vendidos anualmente (value.key)
     *                   número de clientes que o compraram (value.value.key)
     * @param limit           Limite desejado
     * @return Map<Integer,Map.Entry<String,Integer>> -> Estrutura que contem a informação necessária para responder a a querie 6
     */
    public Map<Integer,Map.Entry<String,Integer>> Querie6Test (int limit){
        //  limit           produtos nClientes
        Map<Integer,Map.Entry<String,Integer>> q6 = new TreeMap<>();
        List<String> produtos = this.v.getVendasVT().stream().collect(Collectors.toMap(Venda::getProduto,Venda::getQuantidade,Integer::sum)).entrySet()
                .stream().sorted((a,b) -> -(a.getValue()-b.getValue())).map(Map.Entry::getKey)
                .limit(limit).collect(Collectors.toList());
        int num;
        List<Integer> clientes = new ArrayList<>();
        for(String s: produtos){
            num = (int) this.v.getVendasVT().stream().filter(a->a.getProduto().equals(s)).map(Venda::getCliente).distinct().count();
            clientes.add(num);
        }
        for(int i = 0; i < limit; i++){
            q6.put(i,new AbstractMap.SimpleEntry<>(produtos.get(i),clientes.get(i)));
        }
        return q6;
    }

    /**
     * Querie 7 -> Funcao que determina para cada filial (key) a lista dos maiores compradores em termos de dinheiro gasto (value.key)
     * @return Map<Integer,List<String>> -> Estrutura utilizada para responder à querie 7.
     */
    public Map<Integer,List<String>> Querie7(){
        Map<Integer,List<String>> q7 = new HashMap<>();
        for(int i = 0; i < N; i++){
            List<String> a = this.filial[i].getClientes().values().stream().sorted(ClieP::compareFaturacao)
                    .limit(3).map(ClieP::getCliente).collect(Collectors.toList());
            q7.put(i,a);
        }
        return q7;
    }

    /**
     * Querie 7 Teste -> Funcao que determina para cada filial (key) a lista dos maiores compradores em termos de dinheiro gasto (value.key)
     * @return Map<Integer,List<String>> -> Estrutura utilizada para responder à querie 7.
     */
    public Map<Integer,Vector<String>> Querie7Test(){
        Map<Integer,Vector<String>> q7 = new TreeMap<>();
        for(int i = 0; i < N; i++){
            Vector<String> a = this.filial[i].getClientes().values().stream().sorted(ClieP::compareFaturacao)
                                   .limit(3).map(ClieP::getCliente).collect(Collectors.toCollection(Vector::new));
            q7.put(i,a);
        }
        return q7;
    }

    /**
     * Querie 8 -> Funcao que determina os X (key)
     *             clientes que mais compraram anualmente (value.key)
     *             número de produtos comprados por um determinado cliente (value.value.key)
     * @param limit        Limite desejado
     * @return Map<Integer,Map.Entry<String,Integer>> -> Estrutura que contem a informação necessária para responder a a querie 8
     */
    public Map<Integer,Map.Entry<String,Integer>> Querie8(int limit){
        //   limit           Clientes nProdutos
        Map<Integer,Map.Entry<String,Integer>> q8 = new HashMap<>();
        List<Map<String,Set<String>>> aux = new ArrayList<>();
        for(int i = 0; i < N; i++){
            Map<String,Set<String>> tmp = this.filial[i].listaProdutos();
            if(tmp != null)
                aux.add(tmp);
        }
        List<String> clientes = aux.stream().flatMap(a->a.entrySet().stream())
                .collect(Collectors.toMap(Map.Entry::getKey,Map.Entry::getValue,(a,b)->{a.addAll(b); return a;}))
                .entrySet().stream().sorted((a,b)->{
                    if(a.getValue().size() != b.getValue().size())
                        return -(a.getValue().size()-b.getValue().size());
                    return a.getKey().compareTo(b.getKey());
                }).map(Map.Entry::getKey).limit(limit).collect(Collectors.toList());
        List<Integer> produtos = new ArrayList<>();
        for(String s: clientes){
            int num = (int) this.v.getVendasVT().stream().filter(a->a.getCliente().equals(s)).distinct().count();
            produtos.add(num);
        }
        for(int i = 0; i < limit; i++){
            q8.put(i,new AbstractMap.SimpleEntry<>(clientes.get(i),produtos.get(i)));
        }

        return q8;
    }

    /**
     * Querie 8 Teste -> Funcao que determina os X (key)
     *                   clientes que mais compraram anualmente (value.key)
     *                   número de produtos comprados por um determinado cliente (value.value.key)
     * @param limit        Limite desejado
     * @return Map<Integer,Map.Entry<String,Integer>> -> Estrutura que contem a informação necessária para responder a a querie 8
     */
    public Map<Integer,Map.Entry<String,Integer>> Querie8Test(int limit){
        //   limit           Clientes nProdutos
        Map<Integer,Map.Entry<String,Integer>> q8 = new TreeMap<>();
        List<Map<String,Set<String>>> aux = new ArrayList<>();
        for(int i = 0; i < N; i++){
            Map<String,Set<String>> tmp = this.filial[i].listaProdutos();
            if(tmp != null)
                aux.add(tmp);
        }
        List<String> clientes = aux.stream().flatMap(a->a.entrySet().stream())
                .collect(Collectors.toMap(Map.Entry::getKey,Map.Entry::getValue,(a,b)->{a.addAll(b); return a;}))
                .entrySet().stream().sorted((a,b)->{
                    if(a.getValue().size() != b.getValue().size())
                        return -(a.getValue().size()-b.getValue().size());
                    return a.getKey().compareTo(b.getKey());
                }).map(Map.Entry::getKey).limit(limit).collect(Collectors.toList());
        List<Integer> produtos = new ArrayList<>();
        for(String s: clientes){
            int num = (int) this.v.getVendasVT().stream().filter(a->a.getCliente().equals(s)).distinct().count();
            produtos.add(num);
        }
        for(int i = 0; i < limit; i++){
            q8.put(i,new AbstractMap.SimpleEntry<>(clientes.get(i),produtos.get(i)));
        }

        return q8;
    }


    /**
     * Querie 9 -> Funcao que dado um produto valido, que determina os X (key)
     *             clientes que mais compraram (value.key)
     *             e o total gasto desse produto pelo cliente (value.value.key)
     * @param produto       Código válido de produto
     * @param limit         Limite desejado
     * @return Map<Integer,Map.Entry<String,Integer>> -> Estrutura que contem a informação necessária para responder a a querie 9
     */
    public Map<Integer,Map.Entry<String,Double>> Querie9(String produto,int limit){
        //   limit            clientes faturacao
        Map<Integer,Map.Entry<String,Double>> q9 = new HashMap<>();
        List<Venda> venda = this.v.getVendasVT().stream().filter(a->a.getProduto()
                .equals(produto)).sorted(Venda::compareQuant).limit(limit)
                .collect(Collectors.toList());
        List<String> cli = venda.stream().map(Venda::getCliente).collect(Collectors.toList());
        List<Double> fat = venda.stream().map(Venda::getFaturacao).collect(Collectors.toList());
        if(limit > cli.size()){
            for (int i = 0; i < cli.size(); i++) {
                q9.put(i, new AbstractMap.SimpleEntry<>(cli.get(i), fat.get(i)));
            }
        }
        else {
            for (int i = 0; i < limit; i++) {
                q9.put(i, new AbstractMap.SimpleEntry<>(cli.get(i), fat.get(i)));
            }
        }
        return q9;
    }

    /**
     * Querie 9 Teste-> Funcao que dado um produto valido, que determina os X (key)
     *                  clientes que mais compraram (value.key)
     *                  e o total gasto desse produto pelo cliente (value.value.key)
     * @param produto       Código válido de produto
     * @param limit         Limite desejado
     * @return Map<Integer,Map.Entry<String,Integer>> -> Estrutura que contem a informação necessária para responder a a querie 9
     */
    public Map<Integer,Map.Entry<String,Double>> Querie9Test(String produto,int limit){
        //   limit            clientes faturacao
        Map<Integer,Map.Entry<String,Double>> q9 = new TreeMap<>();
        List<Venda> venda = this.v.getVendasVT().stream().filter(a->a.getProduto()
                .equals(produto)).sorted(Venda::compareQuant).limit(limit)
                .collect(Collectors.toList());
        List<String> cli = venda.stream().map(Venda::getCliente).collect(Collectors.toList());
        List<Double> fat = venda.stream().map(Venda::getFaturacao).collect(Collectors.toList());
        if(limit > cli.size()){
            for (int i = 0; i < cli.size(); i++) {
                q9.put(i, new AbstractMap.SimpleEntry<>(cli.get(i), fat.get(i)));
            }
        }
        else {
            for (int i = 0; i < limit; i++) {
                q9.put(i, new AbstractMap.SimpleEntry<>(cli.get(i), fat.get(i)));
            }
        }
        return q9;
    }



    /**
     * Querie 10 -> Função que determina mês a mês, filial a filial, a faturacao total para cada produto.
     * @return Map<String,Fatura> -> Estrutura utilizada que responde a querie 10. Em Fatura contem a faturacao.
     */
    public Map<String,Fatura> Querie10(){
        Map<String,Fatura> querie10 = this.f.getFat();
        for(String p: this.p.getProdutos()){
            if(!this.f.contemProduto(p)){
                Fatura f = new Fatura();
                f.setProduto(p);
                querie10.put(p,f);
            }
        }
        return querie10;
    }

    /**
     * Estatistica 1 -> Função que determina o número total de produtos distintos (key),
     *                  o número total de clientes distintos (value.key)
     *                  o número de vendas grátis( Preço = 0.0) (value.value)
     * @return Map.Entry<Integer, Map.Entry<Integer, Integer>> -> Estrutura necessária para responder a partes da estatistica 1
     */
    public Map.Entry<Integer, Map.Entry<Integer, Integer>> estatistica1(){
        List<String> prod = this.v.getVendasVT().stream().map(Venda::getProduto).distinct().collect(Collectors.toList());
        List<String> cli = this.v.getVendasVT().stream().map(Venda::getCliente).distinct().collect(Collectors.toList());
        List<String> vendasGratis = this.v.getVendasVT().stream().filter(a->a.getPreco() == 0).map(Venda::getCliente).collect(Collectors.toList());
        //                                  nProdutos                                  nClientes    nVendas
        return new AbstractMap.SimpleEntry<>(prod.size(), new AbstractMap.SimpleEntry<>(cli.size(),vendasGratis.size()));
    }


    /**
     * Estatistica 2 -> Função que determina mês a mês (key),
     *                  o número total de compras por mês (value.key),
     *                  filial a filial (value.value.key),
     *                  o faturação mês a mês, filial a filial (value.value.value.key)
     *                  o número clientes distintos que compraram (value.value.value.value)
     * @return Map<Integer,Map.Entry<Integer,Map<Integer,Map.Entry<Double,Integer>>>> -> Estrutura utilizada para responder a consulta 2.
     */
    public Map<Integer,Map.Entry<Integer,Map<Integer,Map.Entry<Double,Integer>>>> estatistica2() {
        //   mes               numV      filial             fat     clientes
        Map<Integer,Map.Entry<Integer,Map<Integer,Map.Entry<Double,Integer>>>> e2 = new HashMap<>();
        int i,cli;
        double fatT;
        for(int j = 0; j < 12; j++) {
            Map<Integer,Map.Entry<Double,Integer>> aux = new HashMap<>();
            int mes = j+1;
            int numVendas = this.v.numVendas(mes);
            for (i = 0; i < N; i++) {
                int fil = i+1;
                fatT = this.v.faturacaoVendas(mes,fil);
                cli = this.v.clientesDistinct(mes,fil);
                aux.put(i,new AbstractMap.SimpleEntry<>(fatT, cli));
            }
            e2.put(j,new AbstractMap.SimpleEntry<>(numVendas,aux));
        }
        return e2;
    }


    /**
     * Função utilizada para guardar e estrutura GestVendas num ficheiro em binário
     * @param nomeFicheiro      Nome do ficheiro a guardar
     * @throws IOException
     */
    public void guardaEstado(String nomeFicheiro) throws IOException{
        FileOutputStream f = new FileOutputStream(nomeFicheiro);
        ObjectOutputStream os = new ObjectOutputStream(f);
        os.writeObject(this);
        os.flush();
        os.close();
    }

    /**
     * Função que inicializa a estrutura através de um ficheiro em binário
     * @param nomeFicheiro     Nome do ficheiro onde a ler a estrutura
     * @return GestVendas nova estrutura
     * @throws FileNotFoundException
     * @throws IOException
     * @throws ClassNotFoundException
     */
    public Model carregaEstado(String nomeFicheiro) throws FileNotFoundException, IOException,ClassNotFoundException{
        FileInputStream f = new FileInputStream(nomeFicheiro);
        ObjectInputStream o = new ObjectInputStream(f);
        Model g = (Model) o.readObject();
        this.path = nomeFicheiro;
        o.close();
        return g;
    }

}

