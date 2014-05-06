package org.duarteduarte.li3.data;

import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import org.duarteduarte.li3.data.Artigo;
import org.duarteduarte.li3.util.Factories;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author duarteduarte
 */
public class AutoresAno {

    private Map<String, Autor> autoresAno = null;
    private int numeroArtigos = 0;
    private int totalAutores = 0;

    public AutoresAno() {
        this.autoresAno = new TreeMap<String, Autor>();
    }

    public AutoresAno(AutoresAno aa) {
        this.autoresAno = new TreeMap<String, Autor>();
        this.autoresAno.putAll(aa.getAutoresAno());
        this.numeroArtigos = aa.getNumeroArtigos();
        this.totalAutores = aa.getTotalAutores();
    }

    public int getNumeroArtigos() {
        return numeroArtigos;
    }

    public void setNumeroArtigos(int numeroArtigos) {
        this.numeroArtigos = numeroArtigos;
    }

    public int getTotalAutores() {
        return totalAutores;
    }

    public void setTotalAutores(int totalAutores) {
        this.totalAutores = totalAutores;
    }

    @Override
    public String toString() {
        return "RedeAutores{" + "redeAutores=" + autoresAno + '}';
    }

    public boolean insereAutor(Autor autor) {
        boolean res = false;
        Autor aux = this.autoresAno.get(autor.getNome());
        if(aux==null){
            this.autoresAno.put(autor.getNome(), autor);
            res=true;
            this.totalAutores++;
        }
        else    {
            aux.addCoAutores(autor.getCoAutores());
            aux.incrementaContadores(autor.getNumeroCoAutores(),autor.getnArtigosSolo());
        }
        
        return res;
    }
    
    public void incrementaArtigos(){
        this.numeroArtigos++;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 61 * hash + (this.autoresAno != null ? this.autoresAno.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final AutoresAno other = (AutoresAno) obj;
        if (this.autoresAno != other.autoresAno && (this.autoresAno == null || !this.autoresAno.equals(other.autoresAno))) {
            return false;
        }
        return true;
    }

    public Map<String, Autor> getAutoresAno() {
        return autoresAno;
    }

    public void setArtigosAno(Map<String, Autor> autoresAno) {
        this.autoresAno.clear();
        this.autoresAno.putAll(autoresAno);
    }

    @Override
    public Object clone() {
        return new AutoresAno(this);
    }
}
