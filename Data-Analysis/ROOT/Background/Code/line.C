{
  Double_t chn[2]={111.697,201.816};
   Double_t enr[2]={1460.8,2614.5};

   TGraphErrors graph(2,chn,enr,nullptr,nullptr);
   graph.Draw();

}
