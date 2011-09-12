.. $Id$

<?xml version="1.0" encoding="UTF-8"?>
<?oxygen RNGSchema="http://www.oasis-open.org/docbook/xml/5.0/rng/docbook.rng" type="xml"?>
<!-- # $Id$ -->
<section  xml:id="DataRules" 
    version="5.0"
    xmlns="http://docbook.org/ns/docbook" 
    xmlns:xlink="http://www.w3.org/1999/xlink" 
    xmlns:xi="http://www.w3.org/2001/XInclude"
  >
    <title>Rules for Storing Data Items in NeXus Files</title>
    <para>
      This section describes the rules which apply for storing single data fields in data files.
    </para>
    
    <section xml:id="Design-Naming">
       <title>Naming Conventions</title>
       <para>
        Group and field Names used within NeXus follow a naming convention which is made up from the following rules:
         The names of NeXus <emphasis>group</emphasis>s and 
            <emphasis>field</emphasis>s 
            <indexterm>
              <primary>rules</primary>
              <secondary>NeXus</secondary>
              <tertiary>naming</tertiary>
            </indexterm> 
            must only contain a restricted set of characters.
            This set may be described by this regular expression syntax 
            <link xlink:href="#RegExpName">regular expression syntax</link>:
            <example xml:id="RegExpName">
              <title>Regular expression pattern for NXDL group and field names</title>
              <programlisting language="c"
                >[A-Za-z_][\w_]*</programlisting>
            </example>
            Note that this name pattern starts with a letter (upper or lower case)
            or "<code>_</code>" (underscore), then letters, 
            numbers, and "<code>_</code>" and is limited to no more than 63 characters
            (imposed by the HDF5 rules for names).
            <indexterm>
              <primary>rules</primary>
              <secondary>HDF5</secondary>
            </indexterm>
       </para>
      <para>
        Sometimes it is necessary to combine words in order to build a descriptive name for a data field or a group. 
        In such cases lowercase words are connected by underscores.
        <informalexample>
          <programlisting language="c">number_of_lenses</programlisting>
        </informalexample>
      </para>    
      
        <para>
          For all data fields, only names from the NeXus base class dictionaries are to 
          be used.<footnote><para>The NeXus base classes provide a comprehensive dictionary
          of terms than can be used for each class.</para></footnote>
          If a data field name or even a complete component is missing, 
          please suggest the addition to the NIAC. The addition will usually be 
          accepted provided it is not a duplication of an existing field and 
          adequately documented. 
        </para>
      
    </section>

   <!-- 
        ===============================
        section: NeXus Storage
        ===============================
    -->
    <section xml:id="Design-NeXusDimensions">
        <title>NeXus Storage</title>
        <para> 
            NeXus stores multi dimensional arrays of physical values in C language storage order,
            <indexterm><primary>dimension</primary><secondary>storage order</secondary></indexterm>
            last dimension is the
            fastest varying. This is the rule. <emphasis>Good reasons are required to deviate from this rule.</emphasis>
        </para>    
        <para>
            One good reason to deviate from this rule is the situation where data must be streamed to disk as fast as possible and 
            a conversion to NeXus storage order is not possible. In such cases, exceptions can be made. It is possible 
            to store data in other storage orders in NeXus <!-- TODO What does this say?  Compound thoughts? --> as well as to specify that the data needs to be converted first 
            before being useful. 
        </para>    
            
        <section xml:id="Design-NonCStorageOrder">
           <title>Non C Storage Order</title>
           <para>    
               In order to indicate that the storage order 
               <indexterm><primary>dimension</primary><secondary>storage order</secondary></indexterm>
               is different from C storage order two
               additional data set attributes, offset and stride, have to be stored which together define the storage 
               layout of the data. Offset and stride contain rank numbers according to the rank of the multidimensional 
               data set. Offset describes the step to make when the dimension is multiplied by 1. Stride defines the step to 
               make when incrementing the dimension. This is best explained by some examples.             
           </para>
           <example>
               <title>Offset and Stride for 1 D data:</title>
               <programlisting linenumbering="numbered"
                           ><xi:include href="examples/offset-stride-1d.txt" parse="text"
                           /></programlisting>
           </example>
           
           <example>
               <title>Offset and Stride for 2D Data</title>
               <programlisting linenumbering="numbered"
                           ><xi:include href="examples/offset-stride-2d.txt" parse="text"
                           /></programlisting>
           </example>
   
           <example>
               <title>Offset and Stride for 3D Data</title>
               <programlisting linenumbering="numbered"
                           ><xi:include href="examples/offset-stride-3d.txt" parse="text"
                           /></programlisting>
           </example>
        </section>    
        <section xml:id="Design-DataValueTransformations">
            <!-- TODO Is it too early to include a section about Data Value Transformations and NXformula? -->
            <title>Data Value Transformations</title>
            <para>
                It is possible to store raw values in NeXus data files. Such data has to be stored in 
                special <literal>NXformula</literal> groups together with the data and information required to transform
                it into physical values. 
                <note>
                    <para>NeXus has not yet defined the <literal>NXformula</literal> group for use in NeXus data files.
                        The exact content of the <literal>NXformula</literal> group is still under discussion.</para>
                </note>
            </para>
        </section>
     </section>
    
    <!-- 
        =========================
        section: NeXus Data Types
        =========================
    -->
    <section xml:id="Design-DataTypes">
        <title>NeXus Data Types</title>
        <table>
            <title>Matching regular expressions for NeXus data types</title>
        <!-- 
            Built this table from <code>../xslt/nexus_base.sch</code>

            <sch:let name="NAPItype_INT" value="'NX_INT(8|16|32|64)'"/>
            <sch:let name="NAPItype_FLOAT" value="'NX_FLOAT(32|64)'"/>
            <sch:let name="ARRAY_regexp" value="'(\[0-9\])?'"/>  <!-/- this is not complete -/->
            <sch:let name="NAPItype_regexp"  value="concat('NX_CHAR|',$NAPItype_INT,'|',$NAPItype_FLOAT)"/>
            <sch:let name="ValidItemName_regexp" value="'^[A-Za-z_][A-Za-z0-9_]*$'" />
            <sch:let name="ValidNXClassName_regexp" value="'^NX[A-Za-z0-9_]*$'" />
        -->
            <tgroup cols="2">
                <colspec colwidth="1*"/>
                <colspec colwidth="1*"/>
                <thead>
                    <row>
                        <entry>description</entry>
                        <entry>matching regular expression</entry>
                    </row>
                </thead>
                
                <tbody>
                    <row>
                        <entry>integer</entry>
                        <entry><code>NX_INT(8|16|32|64)</code></entry>
                    </row>
                    <row>
                        <entry>floating-point</entry>
                        <entry><code>NX_FLOAT(32|64)</code></entry>
                    </row>
                    <row>
                        <entry>array</entry>
                        <entry><code>(\[0-9\])?</code></entry>
                    </row>
                    <row>
                        <entry>valid item name</entry>
                        <entry><code>^[A-Za-z_][A-Za-z0-9_]*$</code></entry>
                    </row>
                    <row>
                        <entry>valid class name</entry>
                        <entry><code>^NX[A-Za-z0-9_]*$</code></entry>
                    </row>
                </tbody>
                
            </tgroup>
        </table>
        <para>
            NeXus supports numeric data as either integer or floating-point
            numbers.  A number follows that indicates the number of bits in the word.
            The table above shows the regular expressions that
            matches the data type specifier.
            <glosslist>
                <glossentry>
                    <glossterm>integers</glossterm>
                    <glossdef>
                        <para>
                            <code>NX_INT8</code>,
                            <code>NX_INT16</code>,
                            <code>NX_INT32</code>,
                            or
                            <code>NX_INT64</code>
                        </para>
                    </glossdef>
                </glossentry>
                <glossentry>
                    <glossterm>floating-point numbers</glossterm>
                    <glossdef>
                        <para>
                            <code>NX_FLOAT32</code>
                            or 
                            <code>NX_FLOAT64</code>
                        </para>
                    </glossdef>
                </glossentry>
                <glossentry>
                    <glossterm>date / time stamps</glossterm>
                    <glossdef>
                        <para>
                            <code>NX_DATE_TIME</code>
                            or 
                            <code>ISO8601</code>: 
                            Dates and times are specified using 
                            ISO-8601 standard definitions.
                            <indexterm><primary>date and time</primary></indexterm>
                            Refer to <xref linkend="Design-Dates-Times"/>.
                        </para>
                    </glossdef>
                </glossentry>
                <glossentry>
                    <glossterm>strings</glossterm>
                    <glossdef>
                        <para>
                            All strings are to be encoded in UTF-8. Since most strings in a
                            NeXus file are restricted to a small set of characters and the first 128 characters are standard across encodings,
                            the encoding of most of the strings in a NeXus file will be a moot point.
                            Where encoding in UTF-8 will be important is when recording peoples names in <code>NXuser</code>
                            and text notes in <code>NXnotes</code>.
                        </para>
                        <para>
                          Because the few places where encoding is important also have unpredictable content, as well as the way in which
                          current operating systems handle character encoding, it is practically impossible to test the encoding used. Hence,
                          <code>nxvalidate</code> provides no messages relating to character encoding.
                        </para>
                    </glossdef>
                </glossentry>
                <glossentry>
                    <glossterm>binary data</glossterm>
                    <glossdef>
                        <para>
                            Binary data is to be written as <code>UINT8</code>.
                        </para>
                    </glossdef>
                </glossentry>
                <glossentry>
                    <glossterm>images</glossterm>
                    <glossdef>
                        <para>
                            Binary image data is to be written using <code>UINT8</code>, the same as binary data, but with an accompanying image mime-type.
                            If the data is text, the line terminator is [CR][LF].
                        </para>
                    </glossdef>
                </glossentry>
            </glosslist>
        </para>
        
    <!-- 
        ==============================
        section: NeXus dates and times
        ==============================
    -->
    <section xml:id="Design-Dates-Times">
        <title>NeXus dates and times</title>
        <para>
            NeXus dates and times should be stored using the 
            <indexterm><primary>date and time</primary></indexterm>
            <link xlink:href="http://www.w3.org/TR/NOTE-datetime"
                >ISO 8601</link><footnote><para
                    >ISO 8601: <link xlink:href="http://www.w3.org/TR/NOTE-datetime"
                        ><literal
                            >http://www.w3.org/TR/NOTE-datetime</literal
                        ></link></para></footnote>
            format e.g. <literal>1996-07-31T21:15:22+0600</literal>. 
            The standard also allows for time intervals in fractional seconds
            with <emphasis>1 or more digits of precision</emphasis>.
            This avoids confusion, e.g. between U.S. and European conventions, 
            and is appropriate for machine sorting. 
            <note>
                <para>
                    Note that the <code>T</code> appears literally in the string, 
                    to indicate the beginning of the time element, as specified 
                    in ISO 8601.  It is common to use a space in place of the <code>T</code>.
                    While human-readable, compatibility with the ISO 8601 standard is not 
                    assured with this substitution.
                </para>
            </note>
        </para>
    </section>
        
    </section>

    
     <!-- 
        ==============================
        section: NeXus units
        ==============================
    -->
    <section xml:id="Design-Units">
        <title>NeXus Units</title>
        <para>
            Given the plethora of possible applications of NeXus, it is difficult to 
            define units<indexterm><primary>units</primary></indexterm>
            to use. Therefore, the general rule is that you are free to 
            store data in any unit you find fit. However, any data field must have a 
            units attribute which describes the units, Wherever possible, SI units are 
            preferred. NeXus units <indexterm significance="preferred">
                <primary>units</primary>
        </indexterm> are written as a string attribute (<code>NX_CHAR</code>) 
            and describe the engineering units. The string
            should be appropriate for the value. 
            Values for the NeXus units must be specified in
            a format compatible with <link 
                xlink:href="http://www.unidata.ucar.edu/software/udunits/udunits-2-units.html"
                >Unidata UDunits</link>
      <footnote><para><indexterm>
                <primary>UDunits</primary>
            </indexterm>
            The UDunits specification also includes instructions  for derived units.
            At present, the contents of NeXus <literal>units</literal> attributes
            are not validated in data files.
            <!-- thus backwards compatible --></para></footnote>
             Application definitions may specify units to be used for fields 
            using an 
            <code>enumeration</code>.<indexterm><primary>enumeration</primary></indexterm>
        </para>
    </section>

    <section>
        <title>Linking Multi Dimensional Data with Axis Data</title>
         <para>
            NeXus allows to store multi dimensional arrays of data.
            <indexterm><primary>dimension</primary></indexterm>
            In most cases 
            it is not sufficient to just have the indices into the array as a label for 
            the dimensions of the data. Usually the information which physical value 
            corresponds to an index into a dimension of the multi dimensional data set.
            To this purpose a means is needed to locate appropriate data arrays which describe 
            what each dimension of a multi dimensional data set actually corresponds too. 
            There is a standard HDF facility to do this: it is called dimension scales. 
            <indexterm><primary>dimension</primary><secondary>dimension scales</secondary></indexterm>
            Unfortunately, at a time, there was only one global namespace for dimension scales.
            Thus NeXus had to come up with its own scheme for locating axis data which is described 
            here. A side effect of the NeXus scheme is that it is possible to have multiple 
            mappings of a given dimension to physical data. For example a TOF data set can have the TOF 
            dimension as raw TOF or as energy. 
         </para>
         <para>          
                There are two methods of linking 
                <indexterm>
                    <primary>link</primary>
                </indexterm> 
                each data dimension to its respective dimension scale. 
                The preferred method uses the <code>axes</code> attribute
                to specify the names of each dimension scale.
                <indexterm><primary>dimension</primary><secondary>dimension scales</secondary></indexterm>
                The original method uses the <code>axis</code> attribute to identify
                with an integer the axis whose value is the number of the dimension.
                After describing each of these methods, the two methods will be compared.
                A prerequisite for both methods is that the data fields describing the axis 
                are stored together with the multi dimensional data set whose axes need to be defined 
                in the same NeXus group. If this leads to data duplication, use links.  
            </para>
            
            <section xml:id="Design-Linking-ByName">
                <title>Linking by name using the <code>axes</code> attribute</title>
                <para>The preferred method is to define an attribute of the data itself
                    called <emphasis>axes</emphasis>. 
                    <indexterm><primary>axes</primary></indexterm>
                    The <code>axes</code> attribute contains the names of 
                    each dimension scale as a
                    <indexterm><primary>dimension</primary><secondary>dimension scales</secondary></indexterm>
                    colon (or comma) separated list in the order they appear in C.
                    For example: 
                    <example>
                        <title>Preferred way of denoting axes</title>
                        <programlisting  language="xml" linenumbering="numbered"
                            ><xi:include href="examples/axes-preferred.xml.txt" parse="text"
                            /></programlisting>
                    </example>
                </para>
            </section>
            
                <section xml:id="Design-LinkingByDimNumber">
                <title>Linking by dimension number using the 
                    <code>axis</code> attribute</title>
                <para>
                    The original method is to define an attribute of each dimension
                    scale called <emphasis>axis</emphasis>. 
                    <indexterm><primary>axis</primary></indexterm>
                    It is an integer whose value is the number of
                    the dimension, in order of fastest varying dimension. 
                    <indexterm><primary>dimension</primary><secondary>fastest varying</secondary></indexterm>
                    That is, if the array being stored is data with elements
                    <code>data[j][i]</code> in C and
                    <code>data(i,j)</code> in Fortran, where <code>i</code> is the 
                    time-of-flight index and <code>j</code> is
                    the polar angle index, the <code>NXdata</code> group would contain:
                    <indexterm><primary>NXdata</primary></indexterm>
                    <example>
                        <title>Original way of denoting axes</title>
                        <programlisting  language="xml" linenumbering="numbered"
                                    ><xi:include href="examples/axes-old.xml.txt" 
                                        parse="text"/></programlisting>
                    </example> The <code>axis</code> attribute must 
                    be defined for each dimension scale.
                    The <code>primary</code> attribute is unique to this method of linking.
                </para>
                <para>
                    There are limited circumstances in which more 
                    than one dimension scale 
                    <indexterm><primary>dimension</primary><secondary>dimension scales</secondary></indexterm>
                    for the same data dimension can be included in the same 
                    <code>NXdata</code> group.
                    <indexterm><primary>NXdata</primary></indexterm>
                    The most common is when the dimension scales are 
                    the three components of an 
                    <emphasis>(hkl)</emphasis> scan. In order to
                    handle this case, we have defined another attribute 
                    of type integer called
                    <code>primary</code> whose value determines the order 
                    in which the scale is expected to be
                    chosen for plotting, i.e.
                    <indexterm>
                        <primary>NeXus basic motivation</primary>
                        <secondary>default plot</secondary>
                    </indexterm>
                </para>
                <para>
                    <simplelist>
                        <member>1st choice: <code>primary="1"</code></member>
                        <member>2nd choice: <code>primary="2"</code></member>
                        <member>etc.</member>
                    </simplelist>
                </para>
                <para>
                    If there is more than one scale with the same value of the <code>axis</code> attribute, one
                    of them must have set <code>primary="1"</code>. Defining the <code>primary</code>
                    attribute for the other scales is optional.
                </para>
                <note>
                  <para>
                      The <code>primary</code> attribute can only be 
                      used with the first method of defining dimension scales 
                      <indexterm><primary>dimension</primary><secondary>dimension scales</secondary></indexterm>
                      discussed above. In addition to 
                      the <code>signal</code> data, this
                      group could contain a data set of the same rank
                      <indexterm><primary>rank</primary></indexterm>
                      and dimensions called <code>errors</code>
                      containing the standard deviations of the data.
                  </para>
                </note>
                
            </section>
                <section xml:id="Design-Linking-Discussion">
                <title>Discussion of the two linking methods</title>
                <para>
                    In general the method using the <code>axes</code> attribute on the multi dimensional 
                    data set should be preferred. This leaves the actual axis describing data sets
                    unannotated and allows them to be used as an axis for other multi dimensional
                    data.  This is especially a concern as an axis describing a data set may be linked 
                    into another group where it may describe a completely different dimension
                    <indexterm><primary>dimension</primary><secondary>data set</secondary></indexterm>
                    of another data set. 
                </para>
                <para>    
                    Only when alternative axes definitions are needed, the <code>axis</code> method 
                    should be used to specify an axis of a data set.  This is shown in the example above for 
                    the <code>some_other_angle</code> field where <code>axis="1"</code>
                    denotes another possible primary axis for plotting.  The default
                    axis for plotting carries the <code>primary="1"</code> attribute.
                </para>
               <para>
                    Both methods of linking data axes will be supported in NeXus
                    utilities that identify dimension scales,
                   <indexterm><primary>dimension</primary><secondary>dimension scales</secondary></indexterm>
                    such as <code>NXUfindaxis()</code>. 
                </para>
            </section>
    </section>    
        <section xml:id="Rules-StoringDetectors">
      <title>Storing Detectors</title>
      <para>
         There are very different types of detectors out there. Storing their data 
         can be a challenge. As a general guide line: if the detector has some 
         well defined form, this should be reflected in the data file. A linear 
         detector becomes a linear array, a rectangular detector becomes an 
         array of size <code>xsize</code> times <code>ysize</code>. 
         Some detectors are so irregular that this 
         does not work. Then the detector data is stored as a linear array, with the
         index being detector number till <code>ndet</code>. Such detectors must be accompanied
        by further arrays of length <code>ndet</code> which give 
        <code>azimuthal_angle, polar_angle and distance</code> for each detector. 
      </para>
      <para>
         If data from a time of flight (TOF) instrument must be described, then the 
         TOF dimension becomes the last dimension, for example an area detector of 
        <code>xsize</code> <emphasis>vs.</emphasis> <code>ysize</code> 
        is stored with TOF as an array with dimensions 
        <code>xsize, ysize, 
         ntof</code>.  
      </para>
      </section>
    <section xml:id="Rules-StoringData-Monitors">
      <title>Monitors are Special</title>
        <para>Monitors
            <indexterm>
                <primary>monitor</primary>
            </indexterm>, detectors that measure the properties 
            of the experimental probe rather than the 
            sample, have a special place in NeXus files. Monitors are crucial to normalize data.
            To emphasize their role, monitors are not stored in the 
            <code>NXinstrument</code> hierarchy but on <code>NXentry</code> level 
            in their own groups as there might be multiple monitors. Of special 
            importance is the monitor in a group called <code>control</code>. 
            This is the main monitor against which the data has to be normalized. 
            This group also contains the counting control information, 
            i.e. counting mode, times, etc.
        </para>
        <para>
          Monitor data may be multidimensional. Good examples are scan monitors 
          where a monitor value per scan point is expected or 
          time-of-flight monitors.
        </para>
    </section>
    
</section>