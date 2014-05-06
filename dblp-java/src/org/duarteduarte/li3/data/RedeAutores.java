/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3.data;

import java.io.Serializable;
import java.util.Map;
import org.duarteduarte.li3.util.Factories;

/**
 *
 * @author duarteduarte
 */
public class RedeAutores implements Serializable {

    private String nomeFicheiro;
    private int anoMinimo;
    private int anoMaximo;
    private int totalAutores;

    public int getTotalAutores() {
        return totalAutores;
    }
    
    public void addAutoresArtigo(int numAutores){
        this.totalAutores+=numAutores;
    }
    
    private Map<Integer, AutoresAno> autores;

    public RedeAutores() {
        this.nomeFicheiro = "";
        this.anoMinimo = Integer.MAX_VALUE;
        this.anoMaximo = Integer.MIN_VALUE;
        this.totalAutores=0;
        this.autores = Factories.giveMeMap();
    }

    protected RedeAutores(String nomeFicheiro, int anoMin, int anoMax, Map<Integer, AutoresAno> art) {
        this.nomeFicheiro = nomeFicheiro;
        this.anoMinimo = anoMin;
        this.anoMaximo = anoMax;
        this.autores = Factories.giveMeMap();
        this.autores.putAll(art);
    }

    protected RedeAutores(RedeAutores ra) {
        this.nomeFicheiro = ra.getNomeFicheiro();
        this.anoMinimo = ra.getAnoMinimo();
        this.anoMaximo = ra.getAnoMaximo();
        this.autores = Factories.giveMeMap();
        this.autores.putAll(ra.getAutores());
    }

    public String getNomeFicheiro() {
        return nomeFicheiro;
    }

    public void setNomeFicheiro(String nomeFicheiro) {
        this.nomeFicheiro = nomeFicheiro;
    }

    public int getAnoMinimo() {
        return this.anoMinimo;
    }

    public void setAnoMinimo(int anoMinimo) {
        this.anoMinimo = anoMinimo;
    }

    public int getAnoMaximo() {
        return this.anoMaximo;
    }

    public void setAnoMaximo(int anoMaximo) {
        this.anoMaximo = anoMaximo;
    }

    public AutoresAno getAutoresAno(int ano) {
        AutoresAno res = this.autores.get(ano);

        return (AutoresAno) (res != null ? res.clone() : null);
    }

    public boolean insereAutoresAno(int ano, AutoresAno autores) {
        boolean res = false;
        if (res = (this.autores.put(ano, autores) != null)) {
            this.anoMinimo = (ano < this.anoMinimo) ? ano : this.anoMinimo;
            this.anoMaximo = (ano > this.anoMaximo) ? ano : this.anoMaximo;
        }

        return res;
    }

    public Map<Integer, AutoresAno> getAutores() {
        return this.autores;
    }

    @Override
    public Object clone() {
        return new RedeAutores(this);
    }

    @Override
    public String toString() {
        return "RedeAutores{" + "nomeFicheiro=" + nomeFicheiro + ", anoMinimo=" + anoMinimo + ", anoMaximo=" + anoMaximo + ", artigos=" + autores + '}';
    }
}
