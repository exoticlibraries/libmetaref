import themata

project = 'libmetaref'
copyright = '2020, Exotic Libraries - MIT License'
author = 'Adewale Azeez and Other Contributors'

html_theme_path = [themata.get_html_theme_path()]
html_theme = 'fandango'
master_doc = 'index'
html_favicon = 'libmetaref.png'
html_static_path = ['_static']
html_context = {
    'css_files': ['_static/css/libmetaref.css']
}

extensions = ['m2r2', ]
source_suffix = ['.rst', '.md']

html_theme_options = {
    'index_is_single': True,
    'show_navigators_in_index': False,
    'has_secondary_header': False,
    'navbar_links': [
        ('Doc', 'doc/index'),
        ('Reference', 'reference/index'),
        ('Contribute', 'https://github.com/exoticlibraries/libmetaref/'),
        ('Exotic Libraries', 'https://exoticlibraries.github.io/'),
        ('Support', 'https://exoticlibraries.github.io/pages/support.html')
    ],
    'has_right_sidebar': True,
    'show_navigators': True,
    'toc_title': 'Other Topics',
    'social_icons': [
        ('fab fa-twitter', 'https://twitter.com/exoticlibs'),
        ('fab fa-github', 'https://github.com/exoticlibraries/libmetaref/')
    ],
    "source_root": "https://github.com/exoticlibraries/libmetaref/edit/main/docs/",
    "document_font_size": "15px",
    'text_color': '#292929',
    'header_background_color': '#292929',
    'header_sec_background_color': '#292929',
    'highlight_color': '#64abd9',
    'footer_highlight_color': '#013e66',
    'footer_link_color': '#5682d1',
    'body_link_highlight_color': '#013e66',
    "metadata": {
        "enable": True,
        "url": "https://exoticlibraries.github.io/libmetaref/",
        "type": "website",
        "title": "Reflection library for C Struct. Runtime introspection and intercession.",
        "description": "Reflection library for C Struct. Runtime introspection and intercession for struct fields, supports struct and field annotation.",
        "image": "https://raw.githubusercontent.com/exoticlibraries/libmetaref/main/docs/libmetaref.png",
        "keywords": "thecarisma, c, cpp, c++, exoticlibraries, exotic, libraries, reflection, introspection, struct, runtime",
        "author": "Adewale Azeez"
    },
    "twitter_metadata": {
        "enable": True,
        "card": "summary",
        "site": "@exoticlibs",
        "creator": "@iamthecarisma",
        "title": "Reflection library for C Struct. Runtime introspection and intercession.",
        "description": "Reflection library for C Struct. Runtime introspection and intercession for struct fields, supports struct and field annotation.",
        "image": "https://raw.githubusercontent.com/exoticlibraries/libmetaref/main/docs/libmetaref.png",
    }
}
