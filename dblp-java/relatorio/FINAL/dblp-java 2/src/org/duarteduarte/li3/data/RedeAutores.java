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
    private int totalAutores;
    private Map<Integer, AutoresAno> autores;

    public RedeAutores() {
        this.nomeFicheiro = "";
        this.totalAutores = 0;
        this.autores = Factories.giveMeMap();
    }

    protected RedeAutores(String nomeFicheiro, Map<Integer, AutoresAno> art) {
        this.nomeFicheiro = nomeFicheiro;
        this.autores = Factories.giveMeMap();
        this.autores.putAll(art);
    }

    protected RedeAutores(RedeAutores ra) {
        this.nomeFicheiro = ra.getNomeFicheiro();
        this.autores = Factories.giveMeMap();
        this.autores.putAll(ra.getRedes());
    }

    public int getTotalAutores() {
        return totalAutores;
    }

    public void addAutoresArtigo(int numAutores) {
        this.totalAutores += numAutores;
    }

    public String getNomeFicheiro() {
        return nomeFicheiro;
    }

    public void setNomeFicheiro(String nomeFicheiro) {
        this.nomeFicheiro = nomeFicheiro;
    }

    public AutoresAno getAutoresAno(int ano) {
        return this.autores.get(ano);
    }

    public boolean insereAutoresAno(int ano, AutoresAno autores) {
        return (this.autores.put(ano, autores) != null);
    }

    public Map<Integer, AutoresAno> getRedes() {
        return this.autores;
    }

    @Override
    public Object clone() {
        return new RedeAutores(this);
    }

    @Override
    public String toString() {
        return "RedeAutores{" + "nomeFicheiro=" + nomeFicheiro + ", artigos=" + autores + '}';
    }
}
