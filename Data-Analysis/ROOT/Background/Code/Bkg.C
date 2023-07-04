{
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1111111); // stats box                                                                                                                  
  gStyle->SetOptFit(0); // fit info box                                                                                                                      
  gStyle->GetAttDate()->SetTextColor(1);
  gStyle->SetLabelFont(132,"XYZ");
  gStyle->SetTextFont(132);
  gStyle->SetTitleFont(132,"XYZ");
  gStyle->SetPalette(1);
  gROOT->ForceStyle();

  TCanvas *c0 = new TCanvas("c0"," ",800,600);
  TCanvas *c1 = new TCanvas("c1","",800,600);

  FILE *fp;
  int i;
  const char * filename = "Background_1_1_high_energy_600_1.tsv";
  const char * filename1 = "Background_1_1_high_energy_600_01_06_2019.tsv";
  const char * filename2 = "Background_1_1_high_energy_600_05_12_2019.tsv";
  const char * filename3 = "Background_1_1_high_energy_600_06_12_2019.tsv";
  const char * filename4 = "Background_1_1_high_energy_600_25_06_2019.tsv";
  const char * filename5 = "Background_1_1_high_energy_600_29_05_2019.tsv";
  const char * filename6 = "Background_1_1_high_energy_600_12_02_2020.tsv";
  const char * filename7 = "Background_1_1_high_energy_600_13_02_2020.tsv";
  const char * filename8 = "Background_1_1_high_energy_600_18_02_2020.tsv";
  const char * filename9 = "Background_1_1_high_energy_600_20_02_2020.tsv";
  const char * filename10 = "Background_1_1_high_energy_600_28_02_2020.tsv";

  float t1 = 321207.14;
  float t2 = 678219.22;
  float t3 = 89510.47;
  float t5 = 321207;
  float t6 = 416502.8;
  float t7 = 95295.53;
  float t8 = 95344.41; 
  float t11 = 670186.76;
  float t = t1 + t2 + t3 + t5 + t6 +t7 + t8 + t11;

  float m1 = 15.4823;
  float m2 = 15.0502;
  float m3 = 13.8292;
  float m5 = 15.6438;
  float m6 = 14.7153;
  float m7 = 13.0178;
  float m8 = 12.7047;
  float m11 = 12.802;

  float mbar = 14.1556625;
    
  float	b1 = 103.452;
  float b2 = 26.3107;
  float b3 = 36.9606;
  float b5 = 91.1753;
  float b6 = 30.1437;
  float b7 = 44.8179;
  float b8 = 43.4396;
  float b11 = 30.8593;
  
  TH1F* h1 = new TH1F("h1","Channel",4096,0,4095);
  TH1F* h2 = new TH1F("h2","",4096,0,4095);
  TH1F* h3 = new TH1F("h3","",4096,0,4095);
  TH1F* h4 = new TH1F("h4","",4096,0,4095);
  TH1F* h5 = new TH1F("h5","",4096,0,4095);
  TH1F* h6 = new TH1F("h6","",4096,0,4095);
  TH1F* h7 = new TH1F("h7","",4096,0,4095);
  TH1F* h8 = new TH1F("h8","",4096,0,4095);
  TH1F* h9 = new TH1F("h9","",4096,0,4095);
  TH1F* h10 = new TH1F("h10","",4096,0,4095);
  TH1F* h11 = new TH1F("h11","",4096,0,4095);
  
  const int numL = 4096;
  float *x = new float[numL];
  float *y = new float[numL];
  float *z = new float[numL];

  fp = fopen(filename,"r");
  for(i=0;i<numL;i++)
    {
      fscanf(fp,"%f %f %f",&x[i],&y[i],&z[i]);

      h1->SetBinContent(i,z[i]);

    }
  fclose(fp);

  fp = fopen(filename1,"r");
  for(i=0;i<numL;i++)
    {
      fscanf(fp,"%f %f %f",&x[i],&y[i],&z[i]);

      h2->SetBinContent(i,z[i]);

    }
  fclose(fp);

  fp = fopen(filename2,"r");
  for(i=0;i<numL;i++)
    {
      fscanf(fp,"%f %f %f",&x[i],&y[i],&z[i]);

      h3->SetBinContent(i,z[i]);

    }
  fclose(fp);

  fp = fopen(filename3,"r");
  for(i=0;i<numL;i++)
    {
      fscanf(fp,"%f %f %f",&x[i],&y[i],&z[i]);

      h4->SetBinContent(i,z[i]);

    }
  fclose(fp);

  fp = fopen(filename4,"r");
  for(i=0;i<numL;i++)
    {
      fscanf(fp,"%f %f %f",&x[i],&y[i],&z[i]);

      h5->SetBinContent(i,z[i]);

    }
  fclose(fp);

  fp = fopen(filename5,"r");
  for(i=0;i<numL;i++)
    {
      fscanf(fp,"%f %f %f",&x[i],&y[i],&z[i]);

      h6->SetBinContent(i,z[i]);

    }
  fclose(fp);

  fp = fopen(filename6,"r");
  for(i=0;i<numL;i++)
    {
      fscanf(fp,"%f %f %f",&x[i],&y[i],&z[i]);

      h7->SetBinContent(i,z[i]);

    }
  fclose(fp);

  fp = fopen(filename7,"r");
  for(i=0;i<numL;i++)
    {
      fscanf(fp,"%f %f %f",&x[i],&y[i],&z[i]);

      h8->SetBinContent(i,z[i]);

    }
  fclose(fp);

  fp = fopen(filename8,"r");
  for(i=0;i<numL;i++)
    {
      fscanf(fp,"%f %f",&x[i],&y[i]);

      h9->SetBinContent(i,y[i]);

    }
  fclose(fp);

  fp = fopen(filename9,"r");
  for(i=0;i<numL;i++)
    {
      fscanf(fp,"%f %f",&x[i],&y[i]);

      h10->SetBinContent(i,y[i]);

    }
  fclose(fp);

  fp = fopen(filename10,"r");
  for(i=0;i<numL;i++)
    {
      fscanf(fp,"%f %f",&x[i],&y[i]);

      h11->SetBinContent(i,z[i]);

    }
  fclose(fp);

  Double_t maxe = 61400;
  TH1D *g1 = new TH1D("g1","g1",4096,0,maxe);
  TRandom3 *r=new TRandom3(0);
  for(int i=0;i<4096;i++){
        Long64_t eN=h1->GetBinContent(i);
        Double_t e=h1->GetBinCenter(i);
        for(Long64_t j=0;j<eN;j++){
	  Double_t ea=e+r->Rndm()*0.2-0.1;
            ea=m1*ea+b1;
            g1->Fill(ea);
        }
    }
  c0->cd();
  c0->SetLogy();
  g1->Draw();
  
  TH1D *g2 = new TH1D("g2","g2",4096,0,maxe);
  for(int i=0;i<4096;i++){
        Long64_t eN=h2->GetBinContent(i);
        Double_t e=h2->GetBinCenter(i);
        for(Long64_t j=0;j<eN;j++){
            Double_t ea=e+r->Rndm()*0.2-0.1;
            ea=m2*ea+b2;
            g2->Fill(ea);
        }
    }
  g2->SetLineColor(kRed);
  g2->Draw("Same");

  
  TH1D *g3 = new TH1D("g3","g3",4096,0,maxe);
  for(int i=0;i<4096;i++){
        Long64_t eN=h3->GetBinContent(i);
        Double_t e=h3->GetBinCenter(i);
        for(Long64_t j=0;j<eN;j++){
            Double_t ea=e+r->Rndm()*0.2-0.1;
            ea=m3*ea+b3;
            g3->Fill(ea);
        }
    }
  g3->SetLineColor(kGreen);
  g3->Draw("Same");

  TH1D *g5 = new TH1D("g5","g5",4096,0,maxe);
  for(int i=0;i<4096;i++){
        Long64_t eN=h5->GetBinContent(i);
        Double_t e=h5->GetBinCenter(i);
        for(Long64_t j=0;j<eN;j++){
            Double_t ea=e+r->Rndm()*0.2-0.1;
            ea=m5*ea+b5;
            g5->Fill(ea);
        }
    }
  g5->SetLineColor(kYellow);
  g5->Draw("Same");

  TH1D *g6 = new TH1D("g6","g6",4096,0,maxe);
  for(int i=0;i<4096;i++){
        Long64_t eN=h6->GetBinContent(i);
        Double_t e=h6->GetBinCenter(i);
        for(Long64_t j=0;j<eN;j++){
            Double_t ea=e+r->Rndm()*0.2-0.1;
            ea=m6*ea+b6;
            g6->Fill(ea);
        }
    }
  g6->SetLineColor(kOrange);
  g6->Draw("Same");
    
 TH1D *g7 = new TH1D("g7","g7",4096,0,maxe);
  for(int i=0;i<4096;i++){
        Long64_t eN=h7->GetBinContent(i);
        Double_t e=h7->GetBinCenter(i);
        for(Long64_t j=0;j<eN;j++){
            Double_t ea=e+r->Rndm()*0.2-0.1;
            ea=m7*ea+b7;
            g7->Fill(ea);
        }
    }
  g7->SetLineColor(kViolet);
  g7->Draw("Same");

  TH1D *g8 = new TH1D("g8","g8",4096,0,maxe);
  for(int i=0;i<4096;i++){
        Long64_t eN=h8->GetBinContent(i);
        Double_t e=h8->GetBinCenter(i);
        for(Long64_t j=0;j<eN;j++){
            Double_t ea=e+r->Rndm()*0.2-0.1;
            ea=m8*ea+b8;
            g8->Fill(ea);
        }
    }
  g8->SetLineColor(kCyan);
  g8->Draw("Same");

  TH1D *g11 = new TH1D("g11","11",4096,0,maxe);
  for(int i=0;i<4096;i++){
        Long64_t eN=h11->GetBinContent(i);
        Double_t e=h11->GetBinCenter(i);
        for(Long64_t j=0;j<eN;j++){
            Double_t ea=e+r->Rndm()*0.2-0.1;
            ea=m11*ea+11;
            g11->Fill(ea);
        }
    }
  g11->SetLineColor(kPink+1);
  g11->Draw("Same");

  TH1D *hsum = new TH1D("hsum","UNAM #gammaRay",4096,0,maxe);
  hsum->Add(g1,1);
  hsum->Add(g2,1);
  hsum->Add(g3,1);
  hsum->Add(g5,1);
  hsum->Add(g6,1);
  hsum->Add(g7,1);
  hsum->Add(g8,1);
  hsum->Add(g11,1);
  c1->cd();
  c1->SetLogy();
  TH1D *hsum1 = (TH1D *)hsum->Clone("hsum1");
  hsum1->Scale(1/t);
  hsum1->SetTitle("C.U. HEGB;Energy [keV];cts/s");
  hsum1->Draw("hist");
    
  c0->cd();
  leg = new TLegend(0.78,0.1,.98,0.4);
  leg->AddEntry(g1,"10_06_2019","l");
  leg->AddEntry(g2,"01_06_2019","l");
  leg->AddEntry(g3,"05_12_2019","l");
  leg->AddEntry(g5,"25_06_2019","l");
  leg->AddEntry(g6,"29_05_2019","l");
  leg->AddEntry(g7,"12_02_2020","l");
  leg->AddEntry(g8,"13_02_2020","l");
  leg->AddEntry(g11,"28_02_2020","l");
  leg->AddEntry(hsum,"Total","l");
  leg->Draw();

  cout << t << endl;
  
  return 0;
}
