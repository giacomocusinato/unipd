<xs:stylesheet>
  <xs:template match="/">
    <html>
      <body>
        <p>Numero film in visione: <xs:value-of select="count(//spettacoli/film)"/></p>
        <dl>
        <xs:for-each select="//spettacoli/film">
          <dt>
            Titolo: <xs:value-of select="@title"/>
            <xs:if test="note/@vietatoMinori and not(note/vietatoMinori='no')">
              *vietato ai minori di <xs:value-of select="note/@vietatoMinori"/> anni
            </xs:if>
          </dt>
          <dd>Regia: <xs:value-of select="regia"/></dd>
          <dd>Durata: <xs:value-of select="durata"/></dd>
          <dd>Cast: <xs:value-of select="cast | vociOriginali"/></dd>
          <dd>Riassunto: <xs:value-of select="riassunto"/></dd>
        </xs:for-each>
        </dl>
      </body>
    </html>
  </xs:template>
</xs:stylesheet>